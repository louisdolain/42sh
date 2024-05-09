/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** handle_variable
*/

#include "bulletin.h"
#include "basics.h"
#include "my.h"
#include "variables.h"
#include <stdio.h>
#include <stdarg.h>

void my_echo(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void process_variable(char ***parsed_input, char ***env,
    int *res, history_t **list)
{
    static variable_t *var = NULL;
    char *temp = NULL;

    if (my_strcmp((*parsed_input)[0], "set") == 0) {
        add_local(&var, parsed_input);
        return;
    }
    if (my_strcmp((*parsed_input)[0], "unset") == 0) {
        remove_local(&var, (*parsed_input)[1]);
        return;
    }
    if (my_strcmp((*parsed_input)[0], "echo") == 0) {
        if (my_strcmp((*parsed_input)[1], "$term") == 0)
            return print_term(env);
        if (my_strcmp((*parsed_input)[1], "$cwd") == 0)
            return print_cwd();
        temp = find_local(&var, (*parsed_input)[1]);
        if (temp != NULL)
            printf("%s\n", temp);
        else {
            char *temp = array_to_str((*parsed_input));
            printf("%s", temp);
            exit;
        }
    }
}
