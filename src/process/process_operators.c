/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** process_operators
*/

#include "my.h"
#include "process.h"
#include "parsing.h"

static int process_or(token_t *token, char ***env)
{
    int exit_status = 0;

    exit_status = recursive_compute(token->under_tokens[0], env);
    if (exit_status == 0)
        return exit_status;
    return recursive_compute(token->under_tokens[1], env);
}

static int process_and(token_t *token, char ***env)
{
    int exit_status = 0;

    exit_status = recursive_compute(token->under_tokens[0], env);
    if (exit_status != 0)
        return exit_status;
    return recursive_compute(token->under_tokens[1], env);
}

int process_operators(token_t *token, char ***env)
{
    int exit_status = 0;

    if (strcmp(token->separator, "||") == 0) {
        return process_or(token, env);
    } else if (strcmp(token->separator, "&&") == 0) {
        return process_and(token, env);
    } else {
        exit_status = recursive_compute(token->under_tokens[0], env);
        exit_status = recursive_compute(token->under_tokens[1], env);
        return exit_status;
    }
    return exit_status;
}
