/*
** EPITECH PROJECT, 2023
** process
** File description:
** process.c
*/

#include "my.h"
#include "process.h"
#include "parsing.h"

int process_recursive(token_t *token, char ***env)
{
    int exit_status = 0;
    int pipefd[2];
    pid_t pid;

    if (!token->under_tokens) {
        char *temp = handle_backticks(token->content, env);

        free(token->content);
        token->content = temp;
        exit_status = process_command(token->content, env);
        return exit_status;
    }
    if (token->under_tokens[0]->output_redirected && token->under_tokens[0]->output_fd == 1) {
        pipe(pipefd);
        pid = fork();
        if (pid == 0) {
            int saved_stdout = dup(STDOUT_FILENO);
            int saved_stdin = dup(STDIN_FILENO);
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            exit_status = recursive_compute(token->under_tokens[1], env);
            close(STDOUT_FILENO);
            close(STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdin);
            close(saved_stdout);
            close(pipefd[0]);
            exit(exit_status);
        } else {
            int saved_stdout = dup(STDOUT_FILENO);
            int saved_stdin = dup(STDIN_FILENO);
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            exit_status = recursive_compute(token->under_tokens[0], env);
            close(STDOUT_FILENO);
            close(STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdin);
            close(saved_stdout);
            close(pipefd[1]);
            waitpid(pid, &exit_status, 0);
            return WEXITSTATUS(exit_status);
        }
    } else {
        exit_status = recursive_compute(token->under_tokens[0], env);
        exit_status = recursive_compute(token->under_tokens[1], env);
        return exit_status;
    }
    return exit_status;
}

int recursive_compute(token_t *token, char ***env)
{
    int exit_status;
    int saved_out;
    int saved_in;

    if (open_token_input_redirections(token, &saved_in) == EXIT_FAILURE ||
        open_token_output_redirections(token, &saved_out) == EXIT_FAILURE ||
        open_token_double_output_redirections
        (token, &saved_out) == EXIT_FAILURE)
        return EXIT_FAILURE;
    
    exit_status = process_recursive(token, env);
    close_token_redirections(token, saved_in, saved_out);
    return exit_status;
}

static token_t *create_token(char *user_input)
{
    token_t *token = calloc(1, sizeof(token_t));

    if (!token)
        return NULL;
    token->input_fd = 0;
    token->output_fd = 1;
    token->content = strdup(user_input);
    if (!verifiy_parantheses(user_input)) {
        free(token);
        return NULL;
    }
    return token;
}

int process_multiple_command(char *user_input, char ***env)
{
    token_t *token = create_token(user_input);
    int exit_status = 0;

    if (!token)
        return 1;
    remove_outer_parentheses(token->content);
    parse_token_redirections(token);
    remove_outer_parentheses(token->content);
    ll_parser(token);
    redirect_tokens(token);
    exit_status = recursive_compute(token, env);
    destroy_tokens(token);
    return exit_status;
}
