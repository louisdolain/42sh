/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** ll_parser
*/

#include "my.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static bool is_on_separator(char *content_ptr, char **separators)
{
    for (int i = 0; separators[i]; i++) {
        if (strncmp(content_ptr, separators[i], strlen(separators[i])) == 0) {
            return true;
        }
    }
    return false;
}

size_t len_to_next_token(char *content_ptr, char **separators)
{
    size_t len = 0;
    bool parenteses_found = false;
    int count = 0;

    while (*content_ptr) {
        if (*content_ptr == '(') {
            count += 1;
            parenteses_found = true;
        }
        if (*content_ptr == ')')
            count -= 1;
        if ((parenteses_found == false || count == 0) &&
            is_on_separator(content_ptr, separators))
            break;
        content_ptr++;
        len++;
    }
    return len;
}

static char *get_separator(char **content_ptr, char **separators)
{
    char *sep = NULL;

    for (int i = 0; separators[i]; i++)
        if (strncmp((*content_ptr), separators[i], strlen(separators[i])) == 0) {
            sep = strndup(*content_ptr, strlen(separators[i]));
            *content_ptr += strlen(separators[i]);
            return sep;
        }
    return NULL;
}

token_t *ll_parser(token_t *head)
{
    char *separators[] = {"|", "&&", ";", NULL};
    token_t *token = calloc(1, sizeof(token_t));
    char *content_ptr = head->content;
    remove_outer_parentheses(content_ptr);
    size_t len_token_left = len_to_next_token(content_ptr, separators);

    token->content = strndup(content_ptr, len_token_left);
    token->input_fd = 0;
    token->output_fd = 1;
    remove_outer_parentheses(token->content);
    parse_token_redirections(token);
    remove_outer_parentheses(token->content);
    content_ptr += len_token_left;
    head->separator = get_separator(&content_ptr, separators);
    if (*content_ptr) {
        append_ptr((void ***)&head->under_tokens, token, NULL);
        token = calloc(1, sizeof(token_t));
        token->input_fd = 0;
        token->output_fd = 1;
        token->content = strdup(content_ptr);
        remove_outer_parentheses(token->content);
        parse_token_redirections(token);
        remove_outer_parentheses(token->content);
        append_ptr((void ***)&head->under_tokens, token, NULL);
    } else {
        free(head->content);
        head->content = token->content;
        free(token->separator);
        free(token);
    }
    for (int i = 0; head->under_tokens && head->under_tokens[i]; i++)
        ll_parser(head->under_tokens[i]);
    return head;
}

int redirect_tokens(token_t *token)
{
    if (token->separator && my_strcmp(token->separator, "|") == 0) {
        if (token->under_tokens) {
            token->under_tokens[0]->output_redirected = 1;
            token->under_tokens[1]->input_redirected = 1;
        }
    }
    if (token->separator && my_strcmp(token->separator, "&&") == 0) {
        if (token->under_tokens) {
            token->under_tokens[0]->output_redirected = 0;
            token->under_tokens[1]->input_redirected = 0;
        }
    }
    for (int i = 0; token->under_tokens && token->under_tokens[i]; i++)
        redirect_tokens(token->under_tokens[i]);
    return 0;
}
