/*
** EPITECH PROJECT, 2023
** process
** File description:
** process.c
*/

#include "my.h"
#include <fcntl.h>
#include <string.h>

int my_setenv(char **parsed_input, char ***env, int len_env)
{
    int index = 0;
    char **new_env = NULL;

    if (setenv_error(parsed_input) == 1)
        return 1;
    if (my_getenv(*env, parsed_input[1]) == NULL) {
        new_env = malloc(sizeof(char *) * (len_env + 2));
        for (int i = 0; i < len_env; i++)
            new_env[i] = (*env)[i];
        new_env[len_env] = concat_mem(parsed_input[1], "=", parsed_input[2]);
        new_env[len_env + 1] = NULL;
        free(*env);
        *env = new_env;
    } else {
        while (!str_begin_with((*env)[index], parsed_input[1]))
            index++;
        free((*env)[index]);
        (*env)[index] = concat_mem(parsed_input[1], "=", parsed_input[2]);
    }
    return 0;
}

int process_setenv(char **parsed_input, char ***env)
{
    int len_env = my_strlen_array(*env);
    int len_parsed_input = my_strlen_array(parsed_input);

    if (len_parsed_input == 1)
        return my_putstr_array(*env);
    if (len_parsed_input >= 2 && len_parsed_input <= 3)
        return my_setenv(parsed_input, env, len_env);
    if (len_parsed_input >= 4) {
        write(2, "setenv: Too many arguments.\n", 28);
        return 1;
    }
    return 0;
}

int process_parent(__pid_t pid, char **parsed_input,
    char **paths, char ***env)
{
    int status;
    int res;

    waitpid(pid, &status, 0);
    res = WEXITSTATUS(status);
    process_cd(parsed_input, env, &res);
    process_env(parsed_input, env, &res);
    process_segfault(status, &res);
    free_process(parsed_input, paths);
    return res;
}

static int process_child(char **parsed_input, char **paths, char ***env)
{
    if (my_strcmp(parsed_input[0], "exit") == 0 ||
        my_strcmp(parsed_input[0], "cd") == 0 ||
        my_strcmp(parsed_input[0], "env") == 0 ||
        my_strcmp(parsed_input[0], "setenv") == 0 ||
        my_strcmp(parsed_input[0], "unsetenv") == 0)
        exit(0);
    execve(parsed_input[0], parsed_input, *env);
    execve_error(parsed_input[0]);
    for (int i = 0; paths[i] != NULL; i++)
        execve(paths[i], parsed_input, *env);
    write(2, parsed_input[0], my_strlen(parsed_input[0]));
    write(2, ": Command not found.\n", 21);
    exit(1);
}

void handle_quotes(char *command)
{
    bool in_quote = false;

    for (int i = 0; command[i]; i++) {
        if (command[i] == '\'' && !in_quote) {
            in_quote = true;
            continue;
        }
        else if (command[i] == '\'' && in_quote) {
            in_quote = false;
            continue;
        }
        command[i] = (in_quote && command[i] == ' ' ? -1 : command[i]);
        command[i] = (in_quote && command[i] == '\t' ? -2 : command[i]);
    }
    for (int i = 0; command[i]; i++) {
        if (command[i] == '\'')
            command[i] = ' ';
    }
}

void restore_quotes(char **parsed_input)
{
    for (int i = 0; parsed_input && parsed_input[i]; i++) {
        for (int j = 0; parsed_input[i][j]; j++) {
            parsed_input[i][j] = (parsed_input[i][j] == -1 ? ' ' : parsed_input[i][j]);
            parsed_input[i][j] = (parsed_input[i][j] == -2 ? '\t' : parsed_input[i][j]);
        }
    }
}

static int process_command(char *command, char ***env)
{
    char **bin_path_list = get_bin_path_list(*env);
    char **parsed_input = NULL;
    char **paths = NULL;
    __pid_t pid;

    handle_quotes(command);
    parsed_input = my_str_to_all_array(command, " \t");
    restore_quotes(parsed_input);
    paths = get_fct_paths(bin_path_list, parsed_input[0]);
    free_str_array(bin_path_list);
    pid = fork();
    if (pid == 0) {
        process_child(parsed_input, paths, env);
    } else
        return process_parent(pid, parsed_input, paths, env);
    return 0;
}

int process_recursive(token_t *token, char ***env)
{
    int exit_status = 0;
    int pipefd[2];
    pid_t pid;

    if (!token->under_tokens) {
        exit_status = process_command(handle_backticks(token->content, env), env);
        return exit_status;
    }
    if (token->under_tokens[0]->output_redirected && token->under_tokens[0]->output_fd == 1) {
        pipe(pipefd);
        pid = fork();
        if (pid == 0) {
            int saved_stdout = dup(STDOUT_FILENO);
            int saved_stdin = dup(STDIN_FILENO);
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            exit_status = recursive_compute(token->under_tokens[1], env);
            close(STDOUT_FILENO);
            close(STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdin);
            close(saved_stdout);
            close(pipefd[0]);
            exit(exit_status);
        } else {
            int saved_stdout = dup(STDOUT_FILENO);
            int saved_stdin = dup(STDIN_FILENO);
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            exit_status = recursive_compute(token->under_tokens[0], env);
            close(STDOUT_FILENO);
            close(STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdin);
            close(saved_stdout);
            close(pipefd[1]);
            waitpid(pid, &exit_status, 0);
            return WEXITSTATUS(exit_status);
        }
    } else {
        exit_status = recursive_compute(token->under_tokens[0], env);
        exit_status = recursive_compute(token->under_tokens[1], env);
        return exit_status;
    }
    return exit_status;
}

int recursive_compute(token_t *token, char ***env)
{
    int exit_status;
    int saved_out;
    int saved_in;

    if (token->output_fd == OUTPUT_REDIRECTION) {
        token->output_fd = open(token->output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (token->output_fd == -1)
            perror("");
        saved_out = dup(STDOUT_FILENO);
        dup2(token->output_fd, STDOUT_FILENO);
    }
    if (token->output_fd == OUTPUT_DOUBLE_REDIRECTION) {
        token->output_fd = open(token->output_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (token->output_fd == -1)
            perror("");
        saved_out = dup(STDOUT_FILENO);
        dup2(token->output_fd, STDOUT_FILENO);
    }
    if (token->input_fd == INPUT_REDIRECTION) {
        token->input_fd = open(token->input_file, O_RDONLY);
        if (token->input_fd == -1)
            perror("");
        saved_in = dup(STDIN_FILENO);
        dup2(token->input_fd, STDIN_FILENO);
    }
    exit_status = process_recursive(token, env);
    if (token->output_fd != 1) {
        dup2(saved_out, STDOUT_FILENO);
        close(saved_out);
        close(token->output_fd);
    }
    if (token->input_fd != 0) {
        dup2(saved_in, STDIN_FILENO);
        close(saved_in);
        close(token->input_fd);
    }
    return exit_status;
}

int process_multiple_command(char *user_input, char ***env)
{
    token_t *token = calloc(1, sizeof(token_t));
    token->input_fd = 0;
    token->output_fd = 1;
    token->content = strdup(user_input);
    if (!token)
        return 1;
    if (!verifiy_parantheses(user_input)) {
        free(token);
        return 1;
    }
    remove_outer_parentheses(token->content);
    parse_token_redirections(token);
    remove_outer_parentheses(token->content);
    ll_parser(token);
    redirect_tokens(token);
    return recursive_compute(token, env);
}
