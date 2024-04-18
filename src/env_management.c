/*
** EPITECH PROJECT, 2023
** process
** File description:
** process.c
*/

#include "my.h"

void add_line(char *new_line, char ***env)
{
    char **new_env = NULL;
    int len_env = my_strlen_array(*env);

    new_env = malloc(sizeof(char *) * (len_env + 2));
    for (int i = 0; i < len_env; i++)
        new_env[i] = (*env)[i];
    new_env[len_env] = new_line;
    new_env[len_env + 1] = NULL;
    free(*env);
    *env = new_env;
}

void fill_env(char ***env)
{
    char pwd[2048];

    getcwd(pwd, 2048);
    if (my_getenv(*env, "PATH") == NULL)
        add_line(my_strdup("PATH="), env);
    if (my_getenv(*env, "OLDPWD") == NULL)
        add_line(concat_mem("OLDPWD", "=", pwd), env);
    if (my_getenv(*env, "PWD") == NULL)
        add_line(concat_mem("PWD", "=", pwd), env);
    if (my_getenv(*env, "HOME") == NULL)
        add_line(concat_mem("HOME", "=", "/home"), env);
}
