/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** free_list
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void free_list(history_t **list)
{
    history_t *temp;

    while (*list != NULL) {
        temp = (*list)->next;
        free((*list)->time);
        free((*list)->cmd);
        free(*list);
        *list = temp;
    }
}

void clear_history(history_t **list)
{
    history_t *current = *list;
    history_t *next;

    while (current != NULL){
        next = current->next;
        free(current->time);
        free(current->cmd);
        free(current);
        current = next;
    }
    *list = NULL;
}

void *free_array(char **array)
{
    if (array == NULL)
        return NULL;
    for (int i = 0; array && array[i] != NULL; i++)
        free(array[i]);
    free(array);
    return NULL;
}
