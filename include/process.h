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

int process_multiple_command(char *user_input, config_t *config);
int process_command(char *command, config_t *config);
int open_token_double_output_redirections(token_t *token,
    int *saved_out);
int open_token_input_redirections(token_t *token, int *saved_in);
int open_token_output_redirections(token_t *token, int *saved_out);
void close_token_redirections(token_t *token, int saved_in, int saved_out);
int exec_cmd(char ***parsed_input, char **paths, config_t *config);
int process_operators(token_t *token, config_t *config);
