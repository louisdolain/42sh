/*
** EPITECH PROJECT, 2023
** strcpy
** File description:
** strcpy
*/

#include "basics.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    while (i < n) {
        dest[i] = src[i];
        i = i + 1;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i = i + 1;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strdup(char const *str)
{
    char *cpy = smalloc(sizeof(char) * (my_strlen(str) + 1));

    my_strcpy(cpy, str);
    return cpy;
}

char *my_strndup(char const *str, int n)
{
    char *cpy = smalloc(sizeof(char) * (n + 1));

    my_strncpy(cpy, str, n);
    return cpy;
}
