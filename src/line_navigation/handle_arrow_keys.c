/*
** EPITECH PROJECT, 2024
** handle arrows
** File description:
** 42sh
*/
#include "navigation.h"

void handle_arrow_key(input_t *input_data, char c)
{
    switch (c) {
        case 65:
            handle_up_arrow(input_data);
            break;
        case 66:
            handle_down_arrow(input_data);
            break;
        case 68:
            handle_left_arrow(input_data->cursor_pos);
            break;
        case 67:
            handle_right_arrow(input_data->input,
            input_data->cursor_pos, input_data->input_length);
            break;
    }
}
