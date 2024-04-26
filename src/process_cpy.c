/*
** EPITECH PROJECT, 2023
** process
** File description:
** process.c
*/

#include "my.h"
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

static int process_command(char *command, char ***env)
{
    char **bin_path_list = get_bin_path_list(*env);
    char **parsed_input = my_str_to_all_array(command, " \t");
    char **paths = get_fct_paths(bin_path_list, parsed_input[0]);
    __pid_t pid;

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
        exit_status = process_command(token->command, env);
        return exit_status;
    }
    if (token->under_tokens[0]->output_redirected) {
        pipe(pipefd);
        pid = fork();
        if (pid == 0) {
            int saved_stdout = dup(STDOUT_FILENO);
            int saved_stdin = dup(STDIN_FILENO);
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            exit_status = recursive_compute(token->under_tokens[1], env, 0);
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
            exit_status = recursive_compute(token->under_tokens[0], env, 1);
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
        exit_status = recursive_compute(token->under_tokens[0], env, -1);
        exit_status = recursive_compute(token->under_tokens[1], env, -1);
        return exit_status;
    }
    return exit_status;
}

int recursive_compute(token_t *token, char ***env, int blocked)
{
    redirection_t red = {0};
    int exit_status;
    int saved_out;
    int saved_in;

    if (parse_redirection(token, &red) == 84)
        return 84;
    if (blocked != 1) {
        saved_out = dup(STDOUT_FILENO);
        if (token->output_fd != -1)
            dup2(token->output_fd, STDOUT_FILENO);
    }
    if (blocked != 0) {
        saved_in = dup(STDIN_FILENO);
        if (token->input_fd != -1)
            dup2(token->input_fd, STDIN_FILENO);
    }
    exit_status = process_recursive(token, env);
    if (token->output_fd != -1)
        close(token->output_fd);
    if (blocked != 1) {
        close(STDOUT_FILENO);
        dup2(saved_out, STDOUT_FILENO);
    }
    if (blocked != 0) {
        close(STDIN_FILENO);
        dup2(saved_in, STDIN_FILENO);
    }
    return exit_status;
}

int process_multiple_command(char *user_input, char ***env)
{
    int exit_status = 0;
    token_t *token = calloc(1, sizeof(token_t));

    token->input_fd = -1;
    token->output_fd = -1;
    token->content = strdup(user_input);
    if (!token)
        return 1;
    ll_parser(token);
    redirect_tokens(token);
    exit_status = recursive_compute(token, env, -1);
    return exit_status;
}
