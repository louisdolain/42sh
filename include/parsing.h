/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** parsing
*/

#pragma once

typedef enum fd_state_e {
    INPUT_REDIRECTION = -2,
    OUTPUT_REDIRECTION = -3,
    OUTPUT_DOUBLE_REDIRECTION = -4,
} fd_state_t;

typedef struct token_s {
    char *content;
    char *command;
    char *separator;
    struct token_s **under_tokens;
    int input_redirected;
    int output_redirected;
    int input_fd;
    int output_fd;
    char *input_file;
    char *output_file;
} token_t;
