/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-pierre.lissope
** File description:
** globbing.c
*/

#include "globbing.h"

size_t nbr_wdr(const char *str)
{
    int count = 0;
    int in_word = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            in_word = 0;
        }
        if (str[i] == '*' || str[i] == '?' || str[i] == '[') {
            break;
        }
        if (!in_word && str[i] != ' ') {
            in_word = 1;
            count++;
        }
    }
    return count;
}

int contains_globbing_pattern(const char *str)
{
    return strchr(str, '*') != NULL || strchr(str, '?') != NULL
        || strchr(str, '[') != NULL;
}
