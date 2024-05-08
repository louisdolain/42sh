/*
** EPITECH PROJECT, 2024
** unit tests for delete handling
** File description:
** 42sh
*/

#include <criterion/criterion.h>
#include "navigation.h"

Test(handle_delete, test1_delete)
{
    char input[MAX_INPUT_LENGTH] = "Hello";
    int cursor_pos = 2;
    int len = 5;

    handle_delete(input, &cursor_pos, &len);
    cr_assert_str_eq(input, "Helo");
    cr_assert_eq(cursor_pos, 2);
    cr_assert_eq(len, 4);
}

Test(handle_delete, test2_delete)
{
    char input[MAX_INPUT_LENGTH] = "Hello";
    int cursor_pos = 5;
    int len = 5;

    handle_delete(input, &cursor_pos, &len);
    cr_assert_str_eq(input, "Hello");
    cr_assert_eq(cursor_pos, 5);
    cr_assert_eq(len, 5);
}
