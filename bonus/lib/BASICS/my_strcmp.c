/*
** EPITECH PROJECT, 2023
** strcpy
** File description:
** strcpy
*/

#include "basics.h"

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    if (s1 == NULL || s2 == NULL)
        return 84;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0')
            return 0;
        i++;
    }
    return s1[i] - s2[i];
}

int my_strncmp(char const *s1, char const *s2, int n)
{
    int result = 0;

    for (int i = 0; i < n; i++) {
        if (s1[i] == s2[i]) {
            result = 0;
        }
        if (s1[i] < s2[i]) {
            return (s1[i] - s2[i]);
        }
        if (s1[i] > s2[i]) {
            return (s1[i] - s2[i]);
        }
    }
    result = 0;
    return result;
}
