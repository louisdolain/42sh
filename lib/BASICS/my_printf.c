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

int display_var(va_list args, char *str, int i)
{
    int res = 1;
    char *string;

    res = display_var2(args, str, i);
    if (str[i + 1] == 's') {
        string = va_arg(args, char *);
        if (string == NULL) {
            my_putstr("(null)");
        } else {
            my_putstr(string);
            res = my_strlen(string);
        }
    }
    if (str[i + 1] == 'c')
        my_putchar(va_arg(args, int));
    return res;
}

int mini_printf(char *str, ...)
{
    va_list args;
    int count = 0;

    va_start(args, str);
    for (int i = 0; str[i] != '\0'; i++) {
        if (isntvar(str, i) == 1) {
            my_putchar(str[i]);
            count++;
        }
        if (isntvar(str, i) == 0) {
            count = count + display_var(args, str, i);
            i++;
        }
    }
    va_end(args);
    return count;
}
