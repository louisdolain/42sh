/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** show_history
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "my.h"

void display_history(history_t *list, char *flag)
{
    if (list == NULL)
        return;
    display_history(list->next, flag);
    if (strcmp(flag, "-h") == 0)
        printf("%s\n", list->cmd);
    else
        printf("    %d  %s   %s\n", list->cmd_num, list->time, list->cmd);
}

void display_history_reverse(history_t **list)
{
    history_t *next;
    history_t *current = NULL;

    if (list == NULL)
        return;
    current = *list;
    while (current != NULL) {
        next = current->next;
        printf("    %d  %s   %s\n", current->cmd_num,
        current->time, current->cmd);
        current = next;
    }
}
