/*
** EPITECH PROJECT, 2023
** array
** File description:
** array
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basics.h"

int char_in_str(char c, char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (c == str[i])
            return 1;
    return 0;
}

void put_null(char ***array, int nb_of_line)
{
    *array = my_realloc(*array, sizeof(char *) * (nb_of_line + 0),
        sizeof(char *) * (nb_of_line + 1));
    (*array)[nb_of_line] = NULL;
}

int get_word_len(char *str, char *separators)
{
    int word_len = 0;

    for (char *ptr = str; *ptr != '\0' &&
        !char_in_str(*ptr, separators); ptr++)
        word_len++;
    return word_len;
}

char **my_str_to_all_array(char *str, char *separators)
{
    int nb_of_line = 0;
    int word_len = 0;
    char *entity = NULL;
    char **array = NULL;

    for (str = str; *str != '\0'; str++) {
        word_len = get_word_len(str, separators);
        if (word_len != 0) {
            entity = malloc(sizeof(char) * (word_len + 1));
            entity[word_len] = '\0';
            my_memcpy(entity, str, word_len);
            nb_of_line++;
            array = my_realloc(array, sizeof(char *) * (nb_of_line - 1),
                sizeof(char *) * (nb_of_line));
            array[nb_of_line - 1] = entity;
            str += word_len - 1;
        }
    }
    put_null(&array, nb_of_line);
    return array;
}
