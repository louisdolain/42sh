/*
** EPITECH PROJECT, 2024
** clean str
** File description:
** lib
*/

#include "basics.h"
#include <stdlib.h>


char *cleanstr(char *str)
{
    char *new_str = NULL;
    int end;
    int start = 0;

    if (str == NULL)
        return NULL;
    while (str[start] == ' ' || str[start] == '\t') {
        start++;
    }
    end = my_strlen(str) - 1;
    while (end >= 0 && (str[end] == '\t' || str[end] == ' ')) {
        end--;
    }
    new_str = malloc(sizeof(char) * (end - start + 2));
    my_strncpy(new_str, str + start, end - start + 1);
    free(str);
    return new_str;
}
