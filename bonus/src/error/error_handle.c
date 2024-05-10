/*
** EPITECH PROJECT, 2023
** process
** File description:
** process.c
*/

#include "my.h"

int char_is_letter(char c)
{
    if ((c < 'a' || c > 'z') &&
        (c < 'A' || c > 'Z')) {
        return 0;
    }
    return 1;
}

int char_is_alpha(char c)
{
    if ((c < 'a' || c > 'z') &&
        (c < 'A' || c > 'Z') &&
        (c < '0' || c > '9')) {
        return 0;
    }
    return 1;
}

int str_is_alpha(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (!char_is_alpha(str[i])) {
            return 0;
        }
    }
    return 1;
}

int setenv_error(char ***parsed_input)
{
    char *msg = "setenv: Variable name must begin with a letter.\n";
    char *msg2 =
        "setenv: Variable name must contain alphanumeric characters.\n";

    if (!char_is_letter((*parsed_input)[1][0])) {
        write(2, msg, 48);
        return 1;
    }
    if (!str_is_alpha((*parsed_input)[1])) {
        write(2, msg2, 60);
        return 1;
    }
    return 0;
}

void replace_endline(char *user_input)
{
    if (user_input[my_strlen(user_input) - 1] == '\n')
        user_input[my_strlen(user_input) - 1] = '\0';
}
