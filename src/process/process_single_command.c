/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** process_single_command
*/

#include "my.h"
#include "process.h"

static int process_parent(__pid_t pid, char **parsed_input,
    char **paths, char ***env)
{
    int status;
    int res;

    waitpid(pid, &status, 0);
    res = WEXITSTATUS(status);
    for (int i = 0; BULLETIN_ARRAY[i].bulletin; i++)
        if (strcmp(BULLETIN_ARRAY[i].bulletin, parsed_input[0]) == 0)
            BULLETIN_ARRAY[i].function(parsed_input, env, &res);
    process_segfault(status, &res);
    free_process(parsed_input, paths);
    return res;
}

int process_child(char **parsed_input, char **paths, char ***env)
{
    for (int i = 0; BULLETIN_ARRAY[i].bulletin; i++)
        if (strcmp(BULLETIN_ARRAY[i].bulletin, parsed_input[0]) == 0)
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
        if (command[i] == '\'' && in_quote) {
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
            parsed_input[i][j] = (parsed_input[i][j] == -1 ?
                ' ' : parsed_input[i][j]);
            parsed_input[i][j] = (parsed_input[i][j] == -2 ?
                '\t' : parsed_input[i][j]);
        }
    }
}

int exec_cmd(char **parsed_input,
    char **paths, char ***env)
{
    __pid_t pid;

    pid = fork();
    if (pid == 0) {
        process_child(parsed_input, paths, env);
    } else
        return process_parent(pid, parsed_input, paths, env);
    return 0;
}

int process_command(char *command, char ***env)
{
    char **bin_path_list = get_bin_path_list(*env);
    char **parsed_input = NULL;
    char **paths = NULL;

    handle_quotes(command);
    parsed_input = my_str_to_all_array(command, " \t");
    restore_quotes(parsed_input);
    paths = get_fct_paths(bin_path_list, parsed_input[0]);
    if (contains_globbing_pattern(command)) {
        handle_globbing(command, parsed_input, paths, env);
        return 0;
    }
    free_str_array(bin_path_list);
    return exec_cmd(parsed_input, paths, env);
}
