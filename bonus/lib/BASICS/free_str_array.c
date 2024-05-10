/*
** EPITECH PROJECT, 2023
** pr1
** File description:
** my_print_alpha
*/

#include "basics.h"

void free_str_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
