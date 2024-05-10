/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** parsing
*/

#pragma once

#include "basics.h"

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

void destroy_tokens(token_t *tokens);
void remove_outer_parentheses(char *content_ptr);
token_t *ll_parser(token_t *head);
int redirect_tokens(token_t *token);
void parse_token_redirections(token_t *token);
