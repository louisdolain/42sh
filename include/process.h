/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** process
*/

#pragma once

#include <string.h>
#include <fcntl.h>
#include "bulletin.h"

int process_multiple_command(char *user_input, char ***env);
int process_command(char *command, char ***env);