/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** backticks
*/

#include <string.h>
#include "my.h"

static char *append_char(char **string, char c)
{
    int old_string_len = strlen(*string);

    *string = realloc(*string, old_string_len + 2);
    (*string)[old_string_len] = c;
    (*string)[old_string_len + 1] = '\0';
    return *string;
}

static int get_len_cmd(char *user_input)
{
    int len = 0;

    while (*user_input && *user_input != '`') {
        len++;
        user_input++;
    }
    return len;
}

static void execute_command(int pipefd[2], char *command,
    char ***env, int saved_stdout)
{
    token_t *token = calloc(1, sizeof(token_t));

    token->input_fd = 0;
    token->output_fd = 1;
    token->content = command;
    remove_outer_parentheses(token->content);
    parse_token_redirections(token);
    remove_outer_parentheses(token->content);
    ll_parser(token);
    redirect_tokens(token);
    dup2(pipefd[1], STDOUT_FILENO);
    recursive_compute(token, env);
    dup2(saved_stdout, STDOUT_FILENO);
    destroy_tokens(token);
}

static char *get_command_result(char *command, char ***env)
{
    int pipefd[2];
    int saved_stdout = dup(STDOUT_FILENO);
    char content[2048];
    size_t size;

    pipe(pipefd);
    execute_command(pipefd, command, env, saved_stdout);
    size = read(pipefd[0], content, 2048);
    content[size] = '\0';
    close(pipefd[0]);
    close(pipefd[1]);
    close(saved_stdout);
    return strdup(content);
}

static int parse_backticks(char **user_input, char **new_str, int *len_cmd)
{
    if (**user_input != '`') {
        append_char(new_str, **user_input);
        return 1;
    }
    (*user_input)++;
    (*len_cmd) = get_len_cmd(*user_input);
    if ((*len_cmd) == 0)
        return 1;
    return 0;
}

char *handle_backticks(char *user_input, char ***env)
{
    char *new_str = calloc(1, sizeof(char));
    int len_cmd = 0;
    char *command_result = NULL;

    for (; *user_input; user_input++) {
        if (parse_backticks(&user_input, &new_str, &len_cmd) == 1)
            continue;
        command_result =
            get_command_result(strndup(user_input, len_cmd), env);
        new_str =
            realloc(new_str, strlen(new_str) + strlen(command_result) + 1);
        strcat(new_str, command_result);
        free(command_result);
        user_input += len_cmd + 1;
    }
    for (int i = 0; new_str[i]; i++)
        new_str[i] = (new_str[i] == '\n' ? ' ' : new_str[i]);
    return new_str;
}
