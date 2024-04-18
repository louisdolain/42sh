/*
** EPITECH PROJECT, 2023
** specific
** File description:
** specific functions
*/

#include "my.h"

void process_unsetenv(char **parsed_input, char ***env)
{
    int index = 0;

    if (my_strlen_array(parsed_input) == 1) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return;
    }
    while ((*env)[index] != NULL &&
        !str_begin_with((*env)[index], parsed_input[1]))
        index++;
    if ((*env)[index] != NULL) {
        free((*env)[index]);
        (*env)[index] = my_strdup("\0");
    } else {
        write(2, "Error: Environement variable not found\n", 39);
    }
}

void process_env(char **parsed_input, char ***env, int *res)
{
    if (my_strcmp(parsed_input[0], "env") == 0) {
        *res = 0;
        my_putstr_array(*env);
    }
    if (my_strcmp(parsed_input[0], "setenv") == 0)
        *res = process_setenv(parsed_input, env);
    if (my_strcmp(parsed_input[0], "unsetenv") == 0) {
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
