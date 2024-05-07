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

static int process_user_input(input_t *input_data)
{
    char *input = input_data->input;
    history_t *hist = input_data->hist;
    char c = input_data->c;

    if (c == '\n') {
        add_to_history(hist, input);
        return 0;
    } else if (c == EOF)
        return EOF;
    else
        handle_rest(input_data, c);
    return 1;
}

int handle_user_input_loop(char *input, int *cursor_pos,
    int *input_length, history_t *hist)
{
    char c;
    input_t input_data;
    int result = 0;

    while (1) {
        print_input(input, *cursor_pos, *input_length);
        c = getchar();
        input_data = (input_t){input, cursor_pos, input_length, hist, c};
        result = process_user_input(&input_data);
        if (result == 0 || result == EOF)
            return result;
    }
}
