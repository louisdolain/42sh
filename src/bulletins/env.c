/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** env
*/

#include "my.h"
#include "process.h"

static int my_setenv(char ***parsed_input, char ***env, int len_env)
{
    int index = 0;
    char **new_env = NULL;

    if (setenv_error(parsed_input) == 1)
        return 1;
    if (my_getenv(*env, (*parsed_input)[1]) == NULL) {
        new_env = malloc(sizeof(char *) * (len_env + 2));
        for (int i = 0; i < len_env; i++)
            new_env[i] = (*env)[i];
        new_env[len_env] = concat_mem((*parsed_input)[1], "=", (*parsed_input)[2]);
        new_env[len_env + 1] = NULL;
        free(*env);
        *env = new_env;
    } else {
        while (!str_begin_with((*env)[index], (*parsed_input)[1]))
            index++;
        free((*env)[index]);
        (*env)[index] = concat_mem((*parsed_input)[1], "=", (*parsed_input)[2]);
    }
    return 0;
}

static int process_setenv(char ***parsed_input, char ***env)
{
    int len_env = my_strlen_array(*env);
    int len_parsed_input = my_strlen_array((*parsed_input));

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

static void process_unsetenv(char ***parsed_input, char ***env)
{
    int index = 0;

    if (my_strlen_array((*parsed_input)) == 1) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return;
    }
    while ((*env)[index] != NULL &&
        !str_begin_with((*env)[index], (*parsed_input)[1]))
        index++;
    if ((*env)[index] != NULL) {
        free((*env)[index]);
        (*env)[index] = my_strdup("\0");
    } else {
        write(2, "Error: Environement variable not found\n", 39);
    }
}

void process_env(char ***parsed_input, char ***env, int *res, history_t **list)
{
    if (my_strcmp((*parsed_input)[0], "env") == 0) {
        *res = 0;
        my_putstr_array(*env);
    }
    if (my_strcmp((*parsed_input)[0], "setenv") == 0)
        *res = process_setenv(parsed_input, env);
    if (my_strcmp((*parsed_input)[0], "unsetenv") == 0) {
        process_unsetenv(parsed_input, env);
        *res = 0;
    }
}

void process_segfault(int status, int *res)
{
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
        write(2, "Segmentation fault\n", 19);
        *res = 11;
    }
}
