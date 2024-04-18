/*
** EPITECH PROJECT, 2023
** process
** File description:
** process.c
*/

#include "my.h"

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

static int process_command(command_t *command, char ***env)
{
    char **bin_path_list = get_bin_path_list(*env);
    char **parsed_input = my_str_to_all_array(command->command, " \t");
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

static int child_recursive(int pipefd[2],
    command_t **child_cmds, char ***env)
{
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);
    int exit_status;

    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    exit_status = recursive_process(child_cmds, env);
    close(STDOUT_FILENO);
    close(STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    dup2(saved_stdin, STDIN_FILENO);
    close(pipefd[0]);
    exit(exit_status);
}

static int parent_recursive(pid_t pid, int pipefd[2],
    command_t *parent_cmd, char ***env)
{
    int exit_status;
    redirection_t red = {0};
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);

    close(pipefd[0]);
    if (parse_redirection(parent_cmd, &red) == 84)
        return 84;
    if (parent_cmd->input_fd != -1)
        dup2(parent_cmd->input_fd, STDIN_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    exit_status = process_command(parent_cmd, env);
    close(STDOUT_FILENO);
    close(STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    dup2(saved_stdin, STDIN_FILENO);
    close(pipefd[1]);
    waitpid(pid, &exit_status, 0);
    return WEXITSTATUS(exit_status);
}

static int no_red_recursive(command_t *parent_cmd,
    command_t **child_cmds, char ***env)
{
    int saved[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};
    redirection_t red = {0};
    int exit_status;

    if (parse_redirection(parent_cmd, &red) == 84)
        return 84;
    if (parent_cmd->output_fd != -1)
        dup2(parent_cmd->output_fd, STDOUT_FILENO);
    if (parent_cmd->input_fd != -1)
        dup2(parent_cmd->input_fd, STDIN_FILENO);
    exit_status = process_command(parent_cmd, env);
    if (parent_cmd->output_fd != -1)
        close(parent_cmd->output_fd);
    close(STDOUT_FILENO);
    close(STDIN_FILENO);
    dup2(saved[1], STDOUT_FILENO);
    dup2(saved[0], STDIN_FILENO);
    if (child_cmds[0])
        exit_status = recursive_process(child_cmds, env);
    return exit_status;
}

int recursive_process(command_t **command_array, char ***env)
{
    command_t *parent_cmd = command_array[0];
    command_t **child_cmds = command_array + 1;
    int pipefd[2];
    pid_t pid;

    if (!parent_cmd->output_redirected) {
        return no_red_recursive(parent_cmd, child_cmds, env);
    } else {
        pipe(pipefd);
        pid = fork();
        if (pid == 0)
            child_recursive(pipefd, child_cmds, env);
        else
            return parent_recursive(pid, pipefd, parent_cmd, env);
    }
    return 0;
}

int process_multiple_command(char *user_input, char ***env)
{
    int exit_status = 0;
    command_t **command_array = get_command_array(user_input);

    if (!command_array)
        return 1;
    exit_status = recursive_process(command_array, env);
    destroy_command_array(command_array);
    return exit_status;
}
