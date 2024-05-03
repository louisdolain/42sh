/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** get_time
*/

#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *my_get_time(void)
{
    char *format = malloc(sizeof(char) * 9);
    time_t temps;
    struct tm date;

    if (!format)
        return NULL;
    time(&temps);
    date = *localtime(&temps);
    strftime(format, 9, "%X", &date);
    format[5] = '\0';
    return format;
}
