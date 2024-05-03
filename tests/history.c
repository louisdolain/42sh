/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** history
*/

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <string.h>
#include "history.h"
#include "basics.h"


Test(FreeList, Test1) {
    history_t *history1 = malloc(sizeof(history_t));
    history1->time = strdup("20 janvier 2004 - 18:00");
    history1->cmd = strdup("birth mahir");
    history1->next = NULL;

    history_t *history2 = malloc(sizeof(history_t));
    history2->time = strdup("3 mai 2024 - 16:08");
    history2->cmd = strdup("Units test writing");
    history2->next = NULL;

    history1->next = history2;

    free_list(&history1);
    cr_assert_null(history1);
}


