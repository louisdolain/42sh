/*
** EPITECH PROJECT, 2023
** specific
** File description:
** specific functions
*/

#include "my.h"

void put_color_ls(char ***parsed_input)
{
    int len = my_strlen_array(*parsed_input);

    if (my_strcmp((*parsed_input)[0], "ls") == 0) {
        *parsed_input = my_realloc(*parsed_input, sizeof(void *) * (len + 1),
            sizeof(void *) * (len + 2));
        (*parsed_input)[len] = my_strdup("--color=auto");
        (*parsed_input)[len + 1] = NULL;
    }
}
