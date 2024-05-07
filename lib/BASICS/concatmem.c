/*
** EPITECH PROJECT, 2023
** array
** File description:
** array
*/

#include "basics.h"

char *concat_mem(char *str1, char *str2, char *str3)
{
    int size = 0;
    char *new_str = NULL;

    if (str1 != NULL)
        size += my_strlen(str1);
    if (str2 != NULL)
        size += my_strlen(str2);
    if (str3 != NULL)
        size += my_strlen(str3);
    new_str = malloc(sizeof(char) * (size + 1));
    new_str[0] = '\0';
    if (str1 != NULL)
        my_strcat(new_str, str1, 0);
    if (str2 != NULL)
        my_strcat(new_str, str2, 0);
    if (str3 != NULL)
        my_strcat(new_str, str3, 0);
    new_str[size] = '\0';
    return new_str;
}

char *concat_mem_2(char *str1, char *str2)
{
    int size = 0;
    char *new_str = NULL;

    if (str1 != NULL)
        size += my_strlen(str1);
    if (str2 != NULL)
        size += my_strlen(str2);
    new_str = malloc(sizeof(char) * (size + 1));
    new_str[0] = '\0';
    if (str1 != NULL)
        my_strcat(new_str, str1, 0);
    if (str2 != NULL)
        my_strcat(new_str, str2, 0);
    new_str[size] = '\0';
    return new_str;
}