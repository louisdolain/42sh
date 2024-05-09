/*
** EPITECH PROJECT, 2024
** MSH
** File description:
** find_local
*/

#include "variables.h"
#include <string.h>
#include <stddef.h>

char *find_local(variable_t **list, char *command)
{
    variable_t *current = *list;

    ++command;
    while (current != NULL) {
        if (strcmp(current->first, command) == 0)
            return current->second;
        current = current->next;
    }
    return NULL;
}
