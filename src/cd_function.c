/*
** EPITECH PROJECT, 2023
** cd
** File description:
** cd.c
*/

#include "my.h"

void replace_old(char *replace_what, char *replace_by, char ***env)
{
    int index = 0;

    while (!str_begin_with((*env)[index], replace_what))
        index++;
    free((*env)[index]);
    (*env)[index] = replace_by;
}

void process_cd_home(char **parsed_input, char ***env, int *res)
{
    char *path = NULL;
    char pwd[2048];
    int len = my_strlen_array(parsed_input);
    char *oldpath = my_getenv(*env, "PWD") + 4;

    if (len == 1 || (len == 2 && parsed_input[1][0] == '~'))
        path = my_getenv(*env, "HOME") + 5;
    if (len == 2 && parsed_input[1][0] == '-')
        path = my_getenv(*env, "OLDPWD") + 7;
    if (chdir(path) == -1) {
        write_error_cd(path);
        *res = 1;
    } else {
        replace_old("OLDPWD", concat_mem("OLDPWD", "=", oldpath), env);
        replace_old("PWD", concat_mem("PWD", "=", getcwd(pwd, 2048)), env);
        *res = 0;
    }
}

void process_basic_cd(char **parsed_input, char ***env, int *res)
{
    int index = 0;
    char pwd[2048];
    char *oldpath = my_getenv(*env, "PWD") + 4;

    while (!str_begin_with((*env)[index], "PWD"))
        index++;
    if (my_strlen_array(parsed_input) > 2) {
        write(2, "cd: Too many arguments.\n", 24);
        *res = 1;
        return;
    }
    if (chdir(parsed_input[1]) == -1) {
        write_error_cd(parsed_input[1]);
        *res = 1;
    } else {
        replace_old("OLDPWD", concat_mem("OLDPWD", "=", oldpath), env);
        replace_old("PWD", concat_mem("PWD", "=", getcwd(pwd, 2048)), env);
        *res = 0;
    }
}

void process_cd(char **parsed_input, char ***env, int *res)
{
    int len = my_strlen_array(parsed_input);

    if (my_strcmp(parsed_input[0], "cd") == 0 &&
        len > 1 &&
        my_strcmp(parsed_input[1], "~") != 0 &&
        my_strcmp(parsed_input[1], "-") != 0) {
        process_basic_cd(parsed_input, env, res);
    }
    if (my_strcmp(parsed_input[0], "cd") == 0 &&
        (parsed_input[1] == NULL ||
        my_strcmp(parsed_input[1], "~") == 0 ||
        my_strcmp(parsed_input[1], "-") == 0)) {
        process_cd_home(parsed_input, env, res);
    }
}
