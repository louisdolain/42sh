/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** process
*/

#pragma once

#include <string.h>
#include <fcntl.h>

typedef struct bulletins_s {
    char *bulletin;
    void (*function) (char **parsed_input, char ***env, int *res);
} bulletins_t;

void process_cd(char **parsed_input, char ***env, int *res);
void process_env(char **parsed_input, char ***env, int *res);
void process_segfault(int status, int *res);

static const bulletins_t BULLETIN_ARRAY[] = {
    {
        .bulletin = "exit",
        .function = NULL
    },
    {
        .bulletin = "cd",
        .function = process_cd
    },
    {
        .bulletin = "env",
        .function = process_env
    },
    {
        .bulletin = "setenv",
        .function = process_env
    },
    {
        .bulletin = "unsetenv",
        .function = process_env
    },
    {
        .bulletin = NULL
    }
};
