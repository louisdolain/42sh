/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** remove_parentheses
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "my.h"

static bool check_closing(char *content_ptr, int *i_open,
    int *i_close)
{
    for (int i = *i_open + 1; content_ptr[i]; i++) {
        if (i == *i_close)
            break;
        if (content_ptr[i] == '(')
            break;
        if (content_ptr[i] == ')')
            return false;
    }
    for (int i = *i_close - 1; i >= 0; i--) {
        if (i == *i_open)
            break;
        if (content_ptr[i] == ')')
            break;
        if (content_ptr[i] == '(')
            return false;
    }
    return true;
}

static bool parantheses_open(char *content_ptr, int *i_open,
    int *open)
{
    for (size_t i = 0; i < strlen(content_ptr); i++) {
        if (content_ptr[i] == '(') {
            *i_open = i;
            (*open)++;
            break;
        } else if (content_ptr[i] != ' ' && content_ptr[i] != '\t')
            return false;
    }
    return true;
}

static bool parantheses_close(char *content_ptr, int *i_close,
    int *close)
{
    for (int i = strlen(content_ptr) - 1; i >= 0; i--) {
        if (content_ptr[i] == ')') {
            *i_close = i;
            (*close)++;
            break;
        } else if (content_ptr[i] != ' ' && content_ptr[i] != '\t')
            return false;
    }
    return true;
}

static bool find_outer_parantheses(char *content_ptr, int *i_open,
    int *i_close)
{
    int open = 0;
    int close = 0;

    if (parantheses_open(content_ptr, i_open, &open) == false) {
        return false;
    }
    if (parantheses_close(content_ptr, i_close, &close) == false) {
        return false;
    }
    if (check_closing(content_ptr, i_open, i_close) == false) {
        return false;
    }
    return open == 1 && close == 1;
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
