/*
** EPITECH PROJECT, 2024
** unit tests for backspace handling
** File description:
** 42sh
*/

#include <criterion/criterion.h>
#include "navigation.h"

Test(handle_backspace, test1_backspace)
{
    char input[MAX_INPUT_LENGTH] = "Hello";
    int cursor_pos = 3;
    int len = 5;

    handle_backspace(input, &cursor_pos, &len);
    cr_assert_str_eq(input, "Helo");
    cr_assert_eq(cursor_pos, 2);
    cr_assert_eq(len, 4);
}

Test(handle_backspace, test2_backspace)
{
    char input[MAX_INPUT_LENGTH] = "Hello";
    int cursor_pos = 0;
    int len = 5;

    handle_backspace(input, &cursor_pos, &len);
    cr_assert_str_eq(input, "Hello");
    cr_assert_eq(cursor_pos, 0);
    cr_assert_eq(len, 5);
}
