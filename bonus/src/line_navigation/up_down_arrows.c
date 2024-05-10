/*
** EPITECH PROJECT, 2024
** handle history commands
** File description:
** 42sh
*/
#include <stdlib.h>
#include <string.h>
#include "navigation.h"

line_history_t *initialize_history(void)
{
    line_history_t *hist = malloc(sizeof(line_history_t));

    hist->history_size = 0;
    hist->current_history_index = -1;
    return hist;
}

void cleanup_history(line_history_t *hist)
{
    for (int i = 0; i < hist->history_size; i++) {
        free(hist->history[i]);
    }
    free(hist);
}

void add_to_history(line_history_t *hist, const char *input)
{
    if (hist->history_size == MAX_HISTORY_SIZE) {
        free(hist->history[0]);
        memmove(hist->history, hist->history + 1,
            (MAX_HISTORY_SIZE - 1) * sizeof(char *));
        hist->history_size--;
    }
    hist->history[hist->history_size] = strdup(input);
    hist->history_size++;
    hist->current_history_index = hist->history_size;
}

static void update_input_from_history(line_history_t *hist, char *input,
    int *input_length, int *cursor_pos)
{
    if (hist->current_history_index == hist->history_size) {
        input[0] = '\0';
        *input_length = 0;
        *cursor_pos = 0;
    } else if (hist->history[hist->current_history_index] != NULL) {
        strcpy(input, hist->history[hist->current_history_index]);
        *input_length = strlen(input);
        *cursor_pos = *input_length;
    }
}

void handle_up_arrow(input_t *input_data)
{
    line_history_t *hist = input_data->hist;
    char *input = input_data->input;
    int *input_length = input_data->input_length;
    int *cursor_pos = input_data->cursor_pos;

    if (hist->current_history_index > 0) {
        hist->current_history_index--;
        if (hist->history[hist->current_history_index] != NULL) {
            strcpy(input, hist->history[hist->current_history_index]);
            *input_length = strlen(input);
            *cursor_pos = *input_length;
        }
    }
}

void handle_down_arrow(input_t *input_data)
{
    line_history_t *hist = input_data->hist;
    char *input = input_data->input;
    int *input_length = input_data->input_length;
    int *cursor_pos = input_data->cursor_pos;

    if (hist->current_history_index < hist->history_size) {
        hist->current_history_index++;
        update_input_from_history(hist, input, input_length, cursor_pos);
    }
}
