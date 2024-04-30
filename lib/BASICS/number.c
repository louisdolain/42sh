/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** is_number
*/

#include "my.h"

int is_number(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return 0;
    return 1;
}

int contain_number(const char *str)
{
    while (*str) {
        if (*str >= '0' && *str <= '9')
            return 1;
        str++;
    }
    return 0;
}


