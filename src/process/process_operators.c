/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** process_operators
*/

#include "my.h"
#include "process.h"
#include "parsing.h"

static int process_or(token_t *token, config_t *config)
{
    int exit_status = 0;

    exit_status = recursive_compute(token->under_tokens[0], config);
    if (exit_status == 0)
        return exit_status;
    return recursive_compute(token->under_tokens[1], config);
}

static int process_and(token_t *token, config_t *config)
{
    int exit_status = 0;

    exit_status = recursive_compute(token->under_tokens[0], config);
    if (exit_status != 0)
        return exit_status;
    return recursive_compute(token->under_tokens[1], config);
}

int process_operators(token_t *token, config_t *config)
{
    int exit_status = 0;

    if (strcmp(token->separator, "||") == 0) {
        return process_or(token, config);
    } else if (strcmp(token->separator, "&&") == 0) {
        return process_and(token, config);
    } else {
        exit_status = recursive_compute(token->under_tokens[0], config);
        exit_status = recursive_compute(token->under_tokens[1], config);
        return exit_status;
    }
    return exit_status;
}
