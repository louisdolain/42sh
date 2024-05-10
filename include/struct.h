/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** struct
*/

#pragma once

#include "history.h"

typedef struct config_s {
    char **env;
    history_t *list;
} config_t;
