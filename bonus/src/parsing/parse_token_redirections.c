/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** parse_token_redirections
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include "parsing.h"

static bool separator_outer_parentheses(char *line)
{
    int count = 0;

    for (int i = 0; line[i]; i++) {
        count += (line[i] == '(' ? 1 : 0);
        count += (line[i] == ')' ? -1 : 0);
        if ((line[i] == '|' || line[i] == ';' || line[i] == '&') &&
            count == 0) {
            return true;
        }
    }
    return false;
}

static bool redirection_outer_parentheses(char *line)
{
    int count = 0;

    for (int i = 0; line[i]; i++) {
        count += (line[i] == '(' ? 1 : 0);
        count += (line[i] == ')' ? -1 : 0);
        if ((line[i] == '<' || line[i] == '>') &&
            count == 0) {
            return true;
        }
    }
    return false;
}

char *tokenize(char *str, int start, int end)
{
    char *newstr = calloc(end - start + 2, sizeof(char));
    int index_str = 0;

    for (int i = start; i <= end; i++) {
        newstr[index_str] = str[i];
        str[i] = ' ';
        index_str++;
    }
    return newstr;
}

static void get_token_redirections(token_t *token,
    char *line, int i, int start)
{
    if (line[start] == '>' && line[start + 1] == '>') {
        token->output_redirected = 1;
        token->output_fd = OUTPUT_DOUBLE_REDIRECTION;
        token->output_file = cleanstr(tokenize(line, start + 2, i - 1));
        line[start] = ' ';
        line[start + 1] = ' ';
        return;
    }
    if (line[start] == '>') {
        token->output_redirected = 1;
        token->output_fd = OUTPUT_REDIRECTION;
        token->output_file = cleanstr(tokenize(line, start + 1, i - 1));
        line[start] = ' ';
    }
    if (line[start] == '<') {
        token->input_redirected = 1;
        token->input_fd = INPUT_REDIRECTION;
        token->input_file = cleanstr(tokenize(line, start + 1, i - 1));
        line[start] = ' ';
    }
}

static void isolate_token(token_t *token)
{
    int count = 0;
    int i = 0;
    int start = 0;
    char *line = token->content;

    for (; line[i]; i++) {
        count += (line[i] == '(' ? 1 : 0);
        count += (line[i] == ')' ? -1 : 0);
        if ((line[i] == '>' || line[i] == '<') && count == 0)
            break;
    }
    if (line[i] == '\0')
        return;
    start = i;
    if (line[i + 1] == '>')
        i++;
    for (i += 1; line[i] && line[i] != '(' && line[i] != '|' &&
        line[i] != '&' && line[i] != ';' && line[i] != '>' &&
        line[i] != '<'; i++);
    get_token_redirections(token, line, i, start);
}

void parse_token_redirections(token_t *token)
{
    if (separator_outer_parentheses(token->content))
        return;
    while (redirection_outer_parentheses(token->content))
        isolate_token(token);
}
