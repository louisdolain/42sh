/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** add_rem_local
*/

#include "variables.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "basics.h"

void add_local(variable_t **list, char ***parsed_input)
{
    variable_t *new = malloc(sizeof(variable_t));

    if (!new) {
        return;
    }
    if (strcmp((*parsed_input)[2], "=") != 0 ||
        my_strlen_array((*parsed_input)) != 4) {
        free(new);
        return;
    }
    new->first = strdup((*parsed_input)[1]);
    new->second = strdup((*parsed_input)[3]);
    new->next = *list;
    *list = new;
}

void remove_local(variable_t **list, char *parsed_input)
{
    variable_t *current = *list;
    variable_t *next;

    while (current != NULL) {
        next = current->next;
        if (strcmp(current->first, parsed_input) == 0) {
            free(current->first);
            free(current->second);
            free(current);
            *list = next;
            return;
        }
        current = next;
    }
}
