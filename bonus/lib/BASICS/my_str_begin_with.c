/*
** EPITECH PROJECT, 2023
** array
** File description:
** array
*/

#include "basics.h"

int str_begin_with(char *str, char *find)
{
    int i = 0;

    if (my_strlen(find) > my_strlen(str))
        return 0;
    for (; find[i] != '\0'; i++) {
        if (find[i] != str[i])
            return 0;
    }
    return (str[i] == '=');
}
