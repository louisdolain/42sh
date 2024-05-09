/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** remove_parentheses
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "parsing.h"

static bool parantheses_open(char *content_ptr, int *i_open,
    int *open)
{
    for (size_t i = 0; i < strlen(content_ptr); i++) {
        if (content_ptr[i] == '(') {
            *i_open = i;
            (*open)++;
            break;
        }
        if (content_ptr[i] != ' ' && content_ptr[i] != '\t')
            return false;
    }
    return true;
}

int find_closing(char *content_ptr, int i_open)
{
    int i = i_open;
    int close = 0;

    while (content_ptr[i]) {
        if (content_ptr[i] == '(')
            close++;
        if (content_ptr[i] == ')')
            close--;
        if (close == 0)
            break;
        i++;
    }
    return i;
}

static bool find_outer_parantheses(char *content_ptr, int *i_open,
    int *i_close)
{
    int open = 0;

    if (parantheses_open(content_ptr, i_open, &open) == false) {
        return false;
    }
    *i_close = find_closing(content_ptr, *i_open);
    if (content_ptr[*i_close] == '\0')
        return false;
    for (int i = *i_close + 1; content_ptr[i]; i++) {
        if (content_ptr[i] != ' ' && content_ptr[i] != '\t')
            return false;
    }
    return true;
}

void remove_outer_parentheses(char *content_ptr)
{
    int i_open = 0;
    int i_close = 0;

    while (find_outer_parantheses(content_ptr, &i_open, &i_close)) {
        content_ptr[i_open] = ' ';
        content_ptr[i_close] = ' ';
    }
}
