/*
** EPITECH PROJECT, 2024
** unit tests for valid input checking
** File description:
** line navigation
*/

#include <criterion/criterion.h>
#include "navigation.h"

Test(input_not_empty, test1_input)
{
    char input[] = "";
    int result = input_not_empty(input);

    cr_assert_eq(result, 0, "Empty input");
}

Test(input_not_empty, test2_input)
{
    char input[] = "  \t\t  ";
    int result = input_not_empty(input);

    cr_assert_eq(result, 0, "Input with only spaces and tabs");
}

Test(input_not_empty, test3_input)
{
    char input[] = "\n";
    int result = input_not_empty(input);

    cr_assert_eq(result, 0, "Input with \n");
}

Test(input_not_empty, test4_input)
{
    char input[] = "Exmpl of a valid input";
    int result = input_not_empty(input);

    cr_assert_eq(result, 1, "Valid input");
}

Test(input_not_empty, test5_input)
{
    char input[] = "  \tHello  \tMarie  \n";
    int result = input_not_empty(input);

    cr_assert_eq(result, 1, "Valid input");
}
