/*
** EPITECH PROJECT, 2024
** MSH
** File description:
** printvar
*/

#include "variables.h"
#include "my.h"
#include "basics.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *my_term(char ***env)
{
    char *temp = my_getenv(*env, "TERM") + 5;

    if (!temp)
        return NULL;
    return temp;
}

char *my_cwd(void)
{
    char *pwd = malloc(sizeof(char) * 2048);

    getcwd(pwd, 2048);
    return pwd;
}
