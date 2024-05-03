/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** get_previous_cmd
*/

#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static char *find_by_command_prefix(history_t **list, char *command)
{
    history_t *current = *list;

    while (current != NULL) {
        if (strncmp(current->cmd, command, strlen(command)) == 0)
            return current->cmd;
        current = current->next;
    }
    return NULL;
}

static char *find_by_command_number(history_t **list, int number)
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

void replace_array(char ***old_array, char **new_array)
{
    int new_size = my_arraylen((void **)new_array);

    for (int i = 0; (*old_array)[i] != NULL; i++)
        free((*old_array)[i]);
    free(*old_array);
    *old_array = malloc(sizeof(char *) * (new_size + 1));
    for (int i = 0; i < new_size; i++) {
        (*old_array)[i] = strdup(new_array[i]);
    }
    (*old_array)[new_size] = NULL;
}

void exclamation_mark(history_t **list, char *command, char ***input)
{
    char *temp = NULL;
    char **new_input = NULL;

    if (list == NULL || *list == NULL ||
        command == NULL || input == NULL || *input == NULL) {
        printf("Error: Invalid arguments in exclamation_mark function\n");
        return;
    }
    temp = find(list, command);
    if (temp == NULL) {
        printf("Error: Command not found in history\n");
        return;
    }
    new_input = my_str_to_all_array(temp, " ");
    if (new_input == NULL) {
        printf("pb de malloc\n");
        return;
    }
    replace_array(input, new_input);
}
