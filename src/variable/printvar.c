/*
** EPITECH PROJECT, 2024
** MSH
** File description:
** printvar
*/

#include "variables.h"
#include "basics.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_term(char ***env)
{
    char *temp = my_getenv(*env, "TERM") + 5;

    if (!temp)
        return;
    printf("%s\n", temp);
    return;
}

void print_cwd(void)
{
    char *pwd = malloc(sizeof(char) * 2048);

    getcwd(pwd, 2048);
    printf("%s\n", pwd);
    free(pwd);
}
