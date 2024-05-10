/*
** EPITECH PROJECT, 2023
** tt
** File description:
** sdhh
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "basics.h"

int check_single(char *str, int i)
{
    if (str[i + 1] != 'd' && str[i + 1] != 'c' &&
        str[i + 1] != 's' && str[i + 1] != 'i' &&
        str[i + 1] != '%') {
        return 1;
    }
    return 0;
}

int len_nb(int nb)
{
    int count = 0;

    while (nb != 0) {
        nb = nb / 10;
        count++;
    }
    return count;
}

int isntvar(char *str, int i)
{
    int result = 1;

    if (str[i + 1] == '\0') {
        return 1;
    } else if (str[i] == '%') {
        result = check_single(str, i);
    }
    return result;
}

int display_var2(va_list args, char *str, int i)
{
    int a = 0;

    if (str[i + 1] == 'd' || str[i + 1] == 'i') {
        a = va_arg(args, int);
        my_put_nbr(a);
        return (len_nb(a));
    }
    if (str[i + 1] != '\0' && str[i + 1] == '%') {
        my_putchar('%');
    }
    return 1;
}
