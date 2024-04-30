/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** len_list
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int len_list(history_t *list)
{
    int i = 0;
    history_t *tmp = list;

    while (tmp != NULL) {
        i++;
        tmp = tmp->next;
    }
    return i;
}
