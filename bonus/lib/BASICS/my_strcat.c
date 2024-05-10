/*
** EPITECH PROJECT, 2023
** strcat
** File description:
** strcat
*/

#include "basics.h"

char *my_strcat(char *dest, char const *src, int u)
{
    int lenDest = my_strlen(dest);
    int i = lenDest;
    int j = u;

    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return dest;
}
