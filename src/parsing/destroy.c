/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** destroy
*/

#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"

void destroy_tokens(token_t *tokens)
{
    free(tokens->content);
    free(tokens->command);
    free(tokens->separator);
    free(tokens->input_file);
    free(tokens->output_file);
    if (tokens->under_tokens) {
        destroy_tokens(tokens->under_tokens[0]);
        destroy_tokens(tokens->under_tokens[1]);
    }
    free(tokens->under_tokens);
    free(tokens);
}
