/*
** EPITECH PROJECT, 2023
** strcpy
** File description:
** strcpy
*/

#include "basics.h"

int my_strcmp(char const *s1, char const *s2)
{
    int result = 0;
    int lenS1 = my_strlen(s1);

    for (int i = 0; i <= lenS1; i++) {
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
