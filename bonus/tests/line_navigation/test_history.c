/*
** EPITECH PROJECT, 2024
** unit tests for history accessing handling
** File description:
** 42sh
*/

#include <stdlib.h>
#include <string.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "navigation.h"

Test(add_to_history, test1_history)
{
    history_t *hist = malloc(sizeof(history_t));

    hist->history_size = 0;
    hist->current_history_index = -1;
    add_to_history(hist, "ls");
    add_to_history(hist, "pwd");
    add_to_history(hist, "ls -la; ls");
    cr_assert_eq(hist->history_size, 3);
    cr_assert_str_eq(hist->history[0], "ls");
    cr_assert_str_eq(hist->history[1], "pwd");
    cr_assert_str_eq(hist->history[2], "ls -la; ls");
    cr_assert_eq(hist->current_history_index, 3);
    for (int i = 0; i < hist->history_size; i++)
        free(hist->history[i]);
    free(hist);
}
