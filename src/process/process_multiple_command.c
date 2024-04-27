/*
** EPITECH PROJECT, 2023
** process
** File description:
** process.c
*/

#include "my.h"
#include "process.h"

int process_recursive(token_t *token, char ***env)
{
    int exit_status = 0;
    int pipefd[2];
    pid_t pid;

    if (!token->under_tokens) {
        exit_status = process_command(handle_backticks(token->content, env), env);
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

    if (token->output_fd == OUTPUT_REDIRECTION) {
        token->output_fd = open(token->output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (token->output_fd == -1) {
            perror("");
            return 1;
        }
        saved_out = dup(STDOUT_FILENO);
        dup2(token->output_fd, STDOUT_FILENO);
    }
    if (token->output_fd == OUTPUT_DOUBLE_REDIRECTION) {
        token->output_fd = open(token->output_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (token->output_fd == -1) {
            perror("");
            return 1;
        }
        saved_out = dup(STDOUT_FILENO);
        dup2(token->output_fd, STDOUT_FILENO);
    }
    if (token->input_fd == INPUT_REDIRECTION) {
        token->input_fd = open(token->input_file, O_RDONLY);
        if (token->input_fd == -1) {
            perror("");
            return 1;
        }
        saved_in = dup(STDIN_FILENO);
        dup2(token->input_fd, STDIN_FILENO);
    }
    exit_status = process_recursive(token, env);
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
    return exit_status;
}

int process_multiple_command(char *user_input, char ***env)
{
    token_t *token = calloc(1, sizeof(token_t));
    token->input_fd = 0;
    token->output_fd = 1;
    token->content = strdup(user_input);
    if (!token)
        return 1;
    if (!verifiy_parantheses(user_input)) {
        free(token);
        return 1;
    }
    remove_outer_parentheses(token->content);
    parse_token_redirections(token);
    remove_outer_parentheses(token->content);
    ll_parser(token);
    redirect_tokens(token);
    return recursive_compute(token, env);
}
