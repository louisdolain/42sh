/*
** EPITECH PROJECT, 2024
** handle keys
** File description:
** 42sh
*/
#include "navigation.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static void handle_printable(char *input, int *cursor_pos,
    int *input_length, char c)
{
    if (*input_length < MAX_INPUT_LENGTH - 1) {
        memmove(input + (*cursor_pos) + 1,
            input + (*cursor_pos), *input_length - (*cursor_pos) + 1);
        input[*cursor_pos] = c;
        printf("%c%s", c, input + (*cursor_pos) + 1);
        for (int i = 0; i < *input_length - (*cursor_pos); i++) {
            printf("\b");
        }
        (*input_length)++;
        (*cursor_pos)++;
    }
}

static void handle_backspace(char *input, int *cursor_pos,
    int *input_length)
{
    if (*cursor_pos > 0) {
        memmove(input + (*cursor_pos) - 1,
            input + (*cursor_pos), *input_length - (*cursor_pos) + 1);
        printf("\b");
        printf("%s ", input + (*cursor_pos) - 1);
        for (int i = 0; i < *input_length - (*cursor_pos) + 1; i++) {
            printf("\b");
        }
        (*input_length)--;
        (*cursor_pos)--;
    }
}

static void handle_delete(char *input, int *cursor_pos, int *input_length)
{
    if (*cursor_pos < *input_length) {
        memmove(input + (*cursor_pos),
            input + (*cursor_pos) + 1, *input_length - (*cursor_pos));
        printf("%s ", input + (*cursor_pos));
        for (int i = 0; i < *input_length - (*cursor_pos); i++) {
            printf("\b");
        }
        (*input_length)--;
    }
}

static void handle_delete_printable(char *input, int *cursor_pos,
    int *input_length, char c)
{
    if (c == 126) {
        handle_delete(input, cursor_pos, input_length);
    } else if (isprint(c)) {
        handle_printable(input, cursor_pos, input_length, c);
    }
}

void handle_rest(input_t *input_data, char c)
{
    char *input = input_data->input;
    int *cursor_pos = input_data->cursor_pos;
    int *input_length = input_data->input_length;

    if (c == 27) {
        getchar();
        handle_arrow_key(input_data, getchar());
    } else if (c == 127 || c == 8) {
        handle_backspace(input, cursor_pos, input_length);
    } else {
        handle_delete_printable(input, cursor_pos, input_length, c);
    }
}
