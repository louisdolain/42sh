/*
** EPITECH PROJECT, 2024
** unit tests for arrows
** File description:
** 42sh
*/

#include <criterion/criterion.h>
#include "navigation.h"

Test(handle_left_arrow, test1_move)
{
    int cursor_pos = 5;

    handle_left_arrow(&cursor_pos);
    cr_assert_eq(cursor_pos, 4);
}

Test(handle_left_arrow, test2_move)
{
    int cursor_pos = 0;

    handle_left_arrow(&cursor_pos);
    cr_assert_eq(cursor_pos, 0);
}
