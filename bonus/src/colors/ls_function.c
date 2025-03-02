/*
** EPITECH PROJECT, 2023
** colors
** File description:
** colors output handling
*/

#include "my.h"
#include "stdlib.h"

void copy_input(int length, char **from, char **to)
{
    for (int i = 0; i < length; i++)
        to[i] = my_strdup(from[i]);
}

void put_color_ls(char ***parsed_input)
{
    int len = my_strlen_array(*parsed_input);
    char **copy_parsed_input = calloc(len + 2, sizeof(char *));

    if (my_strcmp((*parsed_input)[0], "ls") == 0) {
        copy_input(len, *parsed_input, copy_parsed_input);
        copy_parsed_input[len] = my_strdup("--color");
        copy_parsed_input[len + 1] = NULL;
        *parsed_input = copy_parsed_input;
    }
}
