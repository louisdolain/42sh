/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** struct
*/

#pragma once

#include "history.h"
#include "alias.h"

typedef struct config_s {
    char **env;
    history_t *list;
    alias_t **alias_list;
} config_t;
