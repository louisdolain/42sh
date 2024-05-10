/*
** EPITECH PROJECT, 2024
** handle left and right arrows
** File description:
** 42sh
*/
#include <stdio.h>

void handle_left_arrow(int *cursor_pos)
{
    if (*cursor_pos > 0) {
        printf("\b");
        (*cursor_pos)--;
    }
}

void handle_right_arrow(char *input, int *cursor_pos, int *input_length)
{
    if (*cursor_pos < *input_length) {
        printf("%c", input[*cursor_pos]);
        (*cursor_pos)++;
    }
}
