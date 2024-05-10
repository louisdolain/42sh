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

static void execute_command(int fd, char *command,
    config_t *config, int saved_stdout)
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
    dup2(fd, STDOUT_FILENO);
    recursive_compute(token, config);
    dup2(saved_stdout, STDOUT_FILENO);
    destroy_tokens(token);
}

static char *get_command_result(char *command, config_t *config)
{
    int saved_stdout = dup(STDOUT_FILENO);
    int tempfd = open("bacticktempfile",
        O_RDWR | O_CREAT | O_TRUNC, 0666);
    char *content = NULL;

    execute_command(tempfd, command, config, saved_stdout);
    close(tempfd);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    content = open_file("bacticktempfile");
    remove("bacticktempfile");
    if (content == NULL)
        return strdup(" ");
    return content;
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

bool exit_loop(char **user_input, int len_cmd)
{
    for (int j = 0; j < len_cmd + 1 && **user_input; ++j)
        (*user_input)++;
    if (**user_input == '\0')
        return true;
    return false;
}

char *handle_backticks(char *user_input, config_t *config)
{
    char *new_str = calloc(1, sizeof(char));
    int len_cmd = 0;
    char *command_result = NULL;

    for (; *user_input; user_input++) {
        if (parse_backticks(&user_input, &new_str, &len_cmd) == 1)
            continue;
        command_result =
            get_command_result(strndup(user_input, len_cmd), config);
        new_str =
            realloc(new_str, strlen(new_str) + strlen(command_result) + 1);
        strcat(new_str, command_result);
        free(command_result);
        if (exit_loop(&user_input, len_cmd))
            break;
    }
    for (int i = 0; new_str[i]; i++)
        new_str[i] = (new_str[i] == '\n' ? ' ' : new_str[i]);
    return new_str;
}
