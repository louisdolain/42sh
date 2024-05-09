/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** save_history
*/

#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "basics.h"

char **list_to_array(history_t **list)
{
    history_t *ct = *list;
    char **array = malloc((len_list(*list) + 1) * sizeof(char *));
    char *tmp = NULL;
    int index = 0;

    if (array == NULL)
        return NULL;
    array[len_list(*list)] = NULL;
    for (; ct != NULL; index++) {
        tmp = malloc(sizeof(char) * (20 + strlen(ct->time) + strlen(ct->cmd)));
        if (tmp == NULL)
            return free_array(array);
        sprintf(tmp, "    %d  %s  %s",
            ct->cmd_num, ct->time, ct->cmd);
        array[index] = tmp;
        ct = ct->next;
    }
    return array;
}

char *array_to_str(char **array)
{
    int taille = my_arraylen((void **)array);
    int str_size = 0;
    int idx = 0;
    char *str = NULL;

    for (int i = 0; i < taille; i++)
        str_size += strlen(array[i]);
    str = malloc((str_size + taille) * sizeof(char));
    if (!str)
        return NULL;
    for (int i = 0; i < taille; i++) {
        strcpy(str + idx, array[i]);
        idx += strlen(array[i]);
        str[idx] = '\n';
        idx++;
    }
    str[idx - 1] = '\0';
    return str;
}

void my_save(history_t **list)
{
    FILE *fptr;
    char **buffer = list_to_array(list);
    char *str = array_to_str(buffer);

    fptr = fopen(".history", "w");
    fprintf(fptr, "%s", str);
    free_array(buffer);
    free(str);
    fclose(fptr);
}
