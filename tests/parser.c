/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** unit_tests
*/

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include "my.h"


Test(Parser, single_command_no_redirection) {
    command_t **array = get_command_array("ls");

    cr_assert(my_arraylen((void **)array) == 1, "Expected 1 command");
    cr_assert_str_eq(array[0]->command_line, "ls", "Command line mismatch");
    cr_assert_null(array[0]->nextflag, "Nextflag not null");
    cr_assert_eq(array[0]->input_redirected, 0,
        "Input redirection flag incorrect");
    cr_assert_eq(array[0]->output_redirected, 0,
        "Output redirection flag incorrect");
}

Test(Parser, single_command_pipe) {
    command_t **array = get_command_array("rm * | ls");

    cr_assert(my_arraylen((void **)array) == 2, "Expected 1 command");
    cr_assert_str_eq(array[0]->command_line, "rm * ", "Command line mismatch");
    cr_assert_str_eq(array[0]->nextflag, "|", "Nextflag mismatch");
    cr_assert_eq(array[0]->input_redirected, 0,
        "Input redirection flag incorrect");
    cr_assert_eq(array[0]->output_redirected, 1,
        "Output redirection flag incorrect");
    cr_assert_str_eq(array[1]->command_line, " ls", "Command line mismatch");
    cr_assert_null(array[1]->nextflag, "Flag not Null");
    cr_assert_eq(array[1]->input_redirected, 1,
        "Input redirection flag incorrect");
    cr_assert_eq(array[1]->output_redirected, 0,
        "Output redirection flag incorrect");
}

Test(Parser, single_command_semicolon)
{
    command_t **array = get_command_array("ls ; pwd");

    cr_assert(my_arraylen((void **)array) == 2, "Expected 2 commands");

    cr_assert_str_eq(array[0]->command_line, "ls ", "Command line mismatch");
    cr_assert_str_eq(array[0]->nextflag, ";", "Nextflag mismatch");
    cr_assert_eq(array[0]->input_redirected, 0,
        "Input redirection flag incorrect");
    cr_assert_eq(array[0]->output_redirected, 0,
        "Output redirection flag incorrect");
    cr_assert_str_eq(array[1]->command_line, " pwd", "Command line mismatch");
    cr_assert_null(array[1]->nextflag, "Flag not Null");
    cr_assert_eq(array[1]->input_redirected, 0,
        "Input redirection flag incorrect");
    cr_assert_eq(array[1]->output_redirected, 0,
        "Output redirection flag incorrect");
}

Test(Parser, single_command_and)
{
    command_t **array = get_command_array("ls && pwd");

    cr_assert(my_arraylen((void **)array) == 2, "Expected 2 commands");

    cr_assert_str_eq(array[0]->command_line, "ls ", "Command line mismatch");
    cr_assert_str_eq(array[0]->nextflag, "&&", "Nextflag mismatch");
    cr_assert_eq(array[0]->input_redirected, 0,
        "Input redirection flag incorrect");
    cr_assert_eq(array[0]->output_redirected, 0,
        "Output redirection flag incorrect");
    cr_assert_str_eq(array[1]->command_line, " pwd", "Command line mismatch");
    cr_assert_null(array[1]->nextflag, "Flag not Null");
    cr_assert_eq(array[1]->input_redirected, 0,
        "Input redirection flag incorrect");
    cr_assert_eq(array[1]->output_redirected, 0,
        "Output redirection flag incorrect");
}

Test(Parser, multiple_command_pipe) {
    command_t **array = get_command_array("ls | grep hello");

    cr_assert(my_arraylen((void **)array) == 2, "Expected 2 commands");

    cr_assert_str_eq(array[0]->command_line, "ls ", "Command line mismatch");
    cr_assert_str_eq(array[0]->nextflag, "|", "Nextflag mismatch");
    cr_assert_eq(array[0]->input_redirected, 0, "Input redirection flag incorrect");
    cr_assert_eq(array[0]->output_redirected, 1, "Output redirection flag incorrect");

    cr_assert_str_eq(array[1]->command_line, " grep hello", "Command line mismatch");
    cr_assert_null(array[1]->nextflag, "Flag not Null");
    cr_assert_eq(array[1]->input_redirected, 1, "Input redirection flag incorrect");
    cr_assert_eq(array[1]->output_redirected, 0, "Output redirection flag incorrect");
}

Test(Parser, invalid_null_command_after_pipe) {
    command_t **array = get_command_array("ls |");

    cr_assert(array == NULL, "Expected NULL command array");
}

Test(Parser, invalid_null_command_after_and) {
    command_t **array = get_command_array("ls &&");

    cr_assert(array == NULL, "Expected NULL command array");
}

Test(Parser, invalid_null_command_before_and) {
    command_t **array = get_command_array("&& ls");

    cr_assert(array == NULL, "Expected NULL command array");
}

Test(Parser, invalid_null_command_before_pipe) {
    command_t **array = get_command_array("| ls");

    cr_assert(array == NULL, "Expected NULL command array");
}
