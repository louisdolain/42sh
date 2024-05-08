/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** find
*/

#include <string.h>
#include "history.h"
#include "basics.h"

char *find_by_command_prefix(history_t **list, char *command)
{
    history_t *current = *list;

    while (current != NULL) {
        if (strncmp(current->cmd, command, strlen(command)) == 0)
            return current->cmd;
        current = current->next;
    }
    return NULL;
}

char *find_by_command_number(history_t **list, int number)
{
    history_t *current = *list;
    int idx = 1;

    while (current != NULL) {
        if (idx == number)
            return current->cmd;
        idx++;
        current = current->next;
    }
    return NULL;
}

char *find(history_t **list, char *command)
{
    ++command;
    if (contain_number(command) == 1)
        return find_by_command_number(list, atoi(command));
    else
        return find_by_command_prefix(list, command);
}
