/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** arrow_redirections
*/

#include "my.h"
#include "process.h"
#include "parsing.h"

int open_token_double_output_redirections(token_t *token,
    int *saved_out)
{
    if (token->output_fd == OUTPUT_DOUBLE_REDIRECTION) {
        token->output_fd = open(token->output_file,
            O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (token->output_fd == -1) {
            perror("");
            return EXIT_FAILURE;
        }
        (*saved_out) = dup(STDOUT_FILENO);
        dup2(token->output_fd, STDOUT_FILENO);
    }
    return EXIT_SUCCESS;
}

int open_token_input_redirections(token_t *token, int *saved_in)
{
    if (token->input_fd == INPUT_REDIRECTION) {
        token->input_fd = open(token->input_file, O_RDONLY);
        if (token->input_fd == -1) {
            perror("");
            return EXIT_FAILURE;
        }
        (*saved_in) = dup(STDIN_FILENO);
        dup2(token->input_fd, STDIN_FILENO);
    }
    return EXIT_SUCCESS;
}

int open_token_output_redirections(token_t *token, int *saved_out)
{
    if (token->output_fd == OUTPUT_REDIRECTION) {
        token->output_fd = open(token->output_file,
            O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (token->output_fd == -1) {
            perror("");
            return EXIT_FAILURE;
        }
        (*saved_out) = dup(STDOUT_FILENO);
        dup2(token->output_fd, STDOUT_FILENO);
    }
    return EXIT_SUCCESS;
}

void close_token_redirections(token_t *token, int saved_in, int saved_out)
{
    if (token->output_fd != 1) {
        dup2(saved_out, STDOUT_FILENO);
        close(saved_out);
        close(token->output_fd);
    }
    if (token->input_fd != 0) {
        dup2(saved_in, STDIN_FILENO);
        close(saved_in);
        close(token->input_fd);
    }
}
