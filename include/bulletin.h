/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** process
*/

#pragma once

#include <string.h>
#include <fcntl.h>
#include <alias.h>
#include "history.h"
#include "basics.h"

typedef struct bulletins_s {
    char *bulletin;
    void (*function) (char ***parsed_input,
        char ***env, int *res, history_t **list);
} bulletins_t;

void process_cd(char ***parsed_input, char ***env, int *res, history_t **list);
void process_env(char ***parsed_input,
    char ***env, int *res, history_t **list);
void process_segfault(int status, int *res);
int process_alias(char **parsed_input, alias_t *alias_list);
void process_history(char ***parsed_input,
    char ***env, int *res, history_t **list);

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
        .bulletin = "history",
        .function = process_history
    },
    {
        .bulletin = "!",
        .function = process_history
    },
    {
        .bulletin = NULL
    }
};
