/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** process_single_command
*/

#include "my.h"
#include "process.h"
const history_t *list = NULL;
#include "variables.h"

static int char_checker(char *parsed_input, char c)
{
    for (int i = 0; parsed_input[i] != '\0'; i++)
        if (parsed_input[i] == c)
            return 0;
    return 84;
}

static char *search_local_variable(variable_t **var, char *input)
{
    char *result = find_local(var, input);

    if (result != NULL) {
        return strdup(result);
    } else {
        return strdup(input);
    }
}

static char *replace_variable(char *input, variable_t **var, char ***env)
{
    char *result = NULL;

    if (strcmp(input, "$term") == 0) {
        result = strdup(my_term(env));
    } else if (strcmp(input, "$cwd") == 0) {
        result = strdup(my_cwd());
    } else {
        result = search_local_variable(var, input);
    }
    return result;
}

static void replace_variables_in_array(char ***parsed_input,
    variable_t **var, char ***env)
{
    int len = my_arraylen((void **)*parsed_input);
    char **new_array = malloc(sizeof(char *) * (len + 1));

    for (int i = 0; (*parsed_input)[i] != NULL; i++)
        new_array[i] = replace_variable((*parsed_input)[i], var, env);
    new_array[my_arraylen((void **)new_array)] = NULL;
    free(*parsed_input);
    *parsed_input = new_array;
}

static int contain_local_call(char ***parsed_input, char ***env)
{
    static variable_t *var = NULL;

    for (int i = 0; (*parsed_input)[i] != NULL; i++) {
        if (char_checker((*parsed_input)[i], '$') == 0)
            replace_variable(parsed_input, &var, env);
        if (strstr((*parsed_input)[i], "set") != NULL &&
            strstr((*parsed_input)[i], "unset") == NULL &&
            strstr((*parsed_input)[i], "setenv") == NULL &&
            strstr((*parsed_input)[i], "unsetenv") == NULL) {
            add_local(&var, parsed_input);
        }
        if (strstr((*parsed_input)[i], "unset") != NULL &&
            strstr((*parsed_input)[i], "set") == NULL &&
            strstr((*parsed_input)[i], "setenv") == NULL &&
            strstr((*parsed_input)[i], "unsetenv") == NULL) {
            remove_local(&var, (*parsed_input)[i]);
        }
    }
    return 0;
}

static void clean_exiting_process(int status, int res,
    char ***parsed_input, char **paths)
{
    process_segfault(status, &res);
    free_process(parsed_input, paths);
}

static int process_parent(pid_t pid, char ***parsed_input,
    char **paths, char ***env)
{
    int status;
    int res;
    char *temp = strdup(*parsed_input[0]);

    waitpid(pid, &status, 0);
    res = WEXITSTATUS(status);
    for (int i = 0; BULLETIN_ARRAY[i].bulletin; i++) {
    if (((*parsed_input)[0][0] == '!' &&
        strncmp(BULLETIN_ARRAY[i].bulletin, "!", 1) == 0) ||
        strcmp(BULLETIN_ARRAY[i].bulletin, (*parsed_input)[0]) == 0) {
        BULLETIN_ARRAY[i].function(parsed_input, env, &res, &list);
        break;
        }
    }
    if (strcmp(*parsed_input[0], temp) > 0)
        process_multiple_command(array_to_str(*parsed_input), env);
    free(temp);
    clean_exiting_process(status, res, parsed_input, paths);
    return res;
}

int process_child(char ***parsed_input, char **paths, char ***env)
{
    for (int i = 0; BULLETIN_ARRAY[i].bulletin; i++)
        if (((*parsed_input)[0][0] == '!' &&
            strncmp(BULLETIN_ARRAY[i].bulletin, "!", 1) == 0) ||
        strcmp(BULLETIN_ARRAY[i].bulletin, (*parsed_input)[0]) == 0)
            exit(0);
    execve((*parsed_input)[0], (*parsed_input), *env);
    execve_error((*parsed_input)[0]);
    for (int i = 0; paths[i] != NULL; i++)
        execve(paths[i], (*parsed_input), *env);
    write(2, (*parsed_input)[0], my_strlen((*parsed_input)[0]));
    write(2, ": Command not found.\n", 21);
    exit(1);
}

static void handle_quotes(char *command)
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

static void restore_quotes(char ***parsed_input)
{
    for (int i = 0; (*parsed_input) && (*parsed_input)[i]; i++) {
        for (int j = 0; (*parsed_input)[i][j]; j++) {
            (*parsed_input)[i][j] = ((*parsed_input)[i][j] == -1 ?
                ' ' : (*parsed_input)[i][j]);
            (*parsed_input)[i][j] = ((*parsed_input)[i][j] == -2 ?
                '\t' : (*parsed_input)[i][j]);
        }
    }
}

static int exec_cmd(char ***parsed_input,
    char **paths, char ***env)
{
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        process_child(parsed_input, paths, env);
    } else
        return process_parent(pid, parsed_input, paths, env);
    return 0;
}

static int handle_globbing(char ***parsed_input,
    char **paths, char ***env)
{
    glob_t globbuf;
    int i = 0;
    int num_args = 0;

    num_args = count_arguments(parsed_input, num_args);
    if (num_args == 1)
        return -1;
    globbuf.gl_offs = 1;
    while ((*parsed_input)[i]) {
        glob((*parsed_input)[i], GLOB_DOOFFS |
            (i == 0 ? 0 : GLOB_APPEND), NULL, &globbuf);
        i++;
    }
    if (globbuf.gl_pathc == 0) {
        globfree(&globbuf);
        return -1;
    }
    check_glob((*parsed_input), globbuf, i);
    return exec_cmd(&globbuf.gl_pathv, paths, env);
}

int process_command(char *command, char ***env)
{
    char **bin_path_list = get_bin_path_list(*env);
    char **parsed_input = NULL;
    char **paths = NULL;
    pid_t pid;

    handle_quotes(command);
    parsed_input = my_str_to_all_array(command, " \t");
    restore_quotes(&parsed_input);
    paths = get_fct_paths(bin_path_list, parsed_input[0]);
    contain_local_call(&parsed_input, env);
    if (contains_globbing_pattern(command)) {
        handle_globbing(&parsed_input, paths, env);
        return 0;
    }
    free_str_array(bin_path_list);
    return exec_cmd(&parsed_input, paths, env);
}
