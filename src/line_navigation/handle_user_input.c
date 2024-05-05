/*
** EPITECH PROJECT, 2024
** handle user input
** File description:
** 42sh
*/
#include "navigation.h"
#include <string.h>
#include <stdio.h>

int input_not_empty(char *user_input)
{
    if (strlen(user_input) < 2)
        return 0;
    for (int i = 0; user_input[i] != '\0'; i++) {
        if (user_input[i] != '\n' && user_input[i] != ' ' &&
            user_input[i] != '\t')
            return 1;
    }
    return 0;
}

void handle_user_input_loop(char *input, int *cursor_pos,
    int *input_length, history_t *hist)
{
    input_t input_data = { input, cursor_pos, input_length, hist };
    char c;

    while (1) {
        print_input(input, *cursor_pos, *input_length);
        c = getchar();
        if (c == '\n') {
            add_to_history(hist, input);
            break;
        } else {
            handle_rest(&input_data, c);
        }
    }
}
