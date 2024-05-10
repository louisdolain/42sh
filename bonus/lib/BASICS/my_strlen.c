/*
** EPITECH PROJECT, 2023
** pr1
** File description:
** my_print_alpha
*/

#include "basics.h"

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return i;
}

int my_strlen_array(char **array)
{
    int len = 0;

    while (array[len] != NULL)
        len++;
    return len;
}

int my_arraylen(void **array)
{
    int len = 0;

    while (array && array[len])
        len++;
    return len;
}
