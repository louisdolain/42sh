/*
** EPITECH PROJECT, 2024
** Desktop
** File description:
** test
*/

#include "history.h"
#include "bulletin.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void history_add(history_t **list, char *command)
{
    history_t *new = malloc(sizeof(history_t));
    static int i = 1;

    if (!new)
        exit(EXIT_FAILURE);
    new->cmd_num = i;
    new->time = my_get_time();
    new->cmd = strdup(command);
    new->next = *list;
    *list = new;
    i++;
}
