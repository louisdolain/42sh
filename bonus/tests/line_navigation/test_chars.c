/*
** EPITECH PROJECT, 2024
** unit tests to check printable chars
** File description:
** 42sh
*/

#include <criterion/criterion.h>
#include "navigation.h"

Test(handle_printable, test1_char)
{
    char input[MAX_INPUT_LENGTH] = "World";
    int cursor_pos = 3;
    int len = 5;
    char c = '/';

    handle_printable(input, &cursor_pos, &len, c);
    cr_assert_str_eq(input, "Wor/ld");
    cr_assert_eq(cursor_pos, 4);
    cr_assert_eq(len, 6);
}

Test(handle_printable, test2_max)
{
    char input[MAX_INPUT_LENGTH] = "Hi, may shell programming live forever";
    int cursor_pos = MAX_INPUT_LENGTH - 1;
    int len = MAX_INPUT_LENGTH - 1;
    char c = '/';

    handle_printable(input, &cursor_pos, &len, c);
    cr_assert_str_eq(input, "Hi, may shell programming live forever");
    cr_assert_eq(cursor_pos, MAX_INPUT_LENGTH - 1);
    cr_assert_eq(len, MAX_INPUT_LENGTH - 1);
}
