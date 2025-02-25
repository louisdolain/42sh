/*
** EPITECH PROJECT, 2023
** pr1
** File description:
** my_print_alpha
*/

#include "basics.h"

char **my_strdup_array(char **array)
{
    char **new_array;
    int len = my_strlen_array(array);

    new_array = malloc(sizeof(char *) * (len + 1));
    for (int i = 0; i < len; i++)
        new_array[i] = my_strdup(array[i]);
    new_array[len] = NULL;
    return new_array;
}
