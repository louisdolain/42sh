/*
** EPITECH PROJECT, 2023
** cd
** File description:
** cd.c
*/

#include "my.h"

int my_exit(char *userinput, int *exit)
{
    char **parsed = my_str_to_all_array(userinput, " \t");

    if (parsed[0] == NULL) {
        my_fputstr("Parsing failed\n", 2);
    }
    if (my_strcmp(parsed[0], "exit") == 0) {
        if (parsed[1] == NULL) {
            free_str_array(parsed);
            return 1;
        } else {
            my_fputstr("exit: Expression Syntax.\n", 2);
            *exit = 1;
        }
    }
    free_str_array(parsed);
    return 0;
}
