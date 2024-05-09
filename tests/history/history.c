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

Test(free_list_test, Test1) {
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

Test(clear_history_test, Test2) {
    history_t *history1 = malloc(sizeof(history_t));
    history1->time = strdup("20 janvier 2004 - 18:00");
    history1->cmd = strdup("birth mahir");
    history1->next = NULL;

    history_t *history2 = malloc(sizeof(history_t));
    history2->time = strdup("3 mai 2024 - 16:08");
    history2->cmd = strdup("Units test writing");
    history2->next = NULL;

    history1->next = history2;

    clear_history(&history1);
    cr_assert_null(history1);
}

Test(free_array_test, Test3) {
    char **array = malloc(3 * sizeof(char*));
    array[0] = strdup("hello");
    array[1] = strdup("world");
    array[2] = NULL;
    char **result = free_array(array);
    cr_assert_null(result);
    result = free_array(NULL);
    cr_assert_null(result);
    char **short_array = malloc(2 * sizeof(char*));
    short_array[0] = strdup("test");
    short_array[1] = NULL;
    result = free_array(short_array);
    cr_assert_null(result);
}


Test(find_by_command_prefix_test, Test4) {
    history_t *history1 = malloc(sizeof(history_t));
    history1->time = strdup("3 mai 2024 - 16:08");
    history1->cmd = strdup("ls -l");
    history1->next = NULL;
    history_t *history2 = malloc(sizeof(history_t));
    history1->time = strdup("20 janvier 2004 - 18:00");
    history2->cmd = strdup("cd Documents");
    history2->next = NULL;
    history1->next = history2;
    char *result = find_by_command_prefix(&history1, "ls");
    cr_assert_str_eq(result, "ls -l");
    result = find_by_command_prefix(&history1, "apagnan");
    cr_assert_null(result);
}

Test(find_by_command_number_test, Test5) {
    history_t *history1 = malloc(sizeof(history_t));
    history1->time = strdup("3 mai 2024 - 16:08");
    history1->cmd = strdup("ls -l");
    history1->next = NULL;
    history_t *history2 = malloc(sizeof(history_t));
    history1->time = strdup("20 janvier 2004 - 18:00");
    history2->cmd = strdup("cd Documents");
    history2->next = NULL;
    history1->next = history2;
    char *result = find_by_command_number(&history1, 1);
    cr_assert_str_eq(result, "ls -l");
    result = find_by_command_number(&history1, 20);
    cr_assert_null(result);
}

Test(find_test, Test5) {
    history_t *history1 = malloc(sizeof(history_t));
    history1->time = strdup("3 mai 2024 - 16:08");
    history1->cmd = strdup("ls -l");
    history1->next = NULL;
    history_t *history2 = malloc(sizeof(history_t));
    history2->time = strdup("20 janvier 2004 - 18:00");
    history2->cmd = strdup("cd Documents");
    history2->next = NULL;
    history1->next = history2;
    char *result1 = find(&history1, "1");
    char *result2 = find(&history1, "l");
    cr_assert_str_eq(result1, "ls -l");
    cr_assert_str_eq(result2, "ls -l");
}

Test(replace_array_test, Test6) {
    char **old_array = malloc(3 * sizeof(char*));
    old_array[0] = strdup("Hello");
    old_array[1] = strdup("World");
    old_array[2] = NULL;
    char *new_array[] = {"Salut", "Monde", "Mahir", NULL};
    replace_array(&old_array, new_array);
    cr_assert_str_eq(old_array[0], "Salut");
    cr_assert_str_eq(old_array[1], "Monde");
    cr_assert_str_eq(old_array[2], "Mahir");
    cr_assert_null(old_array[3]);
}

Test(exclamation_mark_test, Test7) {
    history_t *history1 = malloc(sizeof(history_t));
    history1->time = strdup("3 mai 2024 - 16:08");
    history1->cmd = strdup("ls -l");
    history1->next = NULL;
    char **input = malloc(3 * sizeof(char*));
    input[0] = strdup("cat");
    input[1] = strdup("file.txt");
    input[2] = NULL;
    exclamation_mark(&history1, "l", &input);
    cr_assert_str_eq(input[0], "ls");
    cr_assert_str_eq(input[1], "-l");
    cr_assert_null(input[2]);
}

Test(len_list_test, Test8) {
    history_t *history1 = malloc(sizeof(history_t));
    history1->time = strdup("3 mai 2024 - 16:08");
    history1->cmd = strdup("ls -l");
    history1->next = NULL;
    history_t *history2 = malloc(sizeof(history_t));
    history2->time = strdup("20 janvier 2004 - 18:00");
    history2->cmd = strdup("cd Documents");
    history2->next = NULL;
    history1->next = history2;
    int result = len_list(history1);
    cr_assert_eq(result, 2);
}

Test(history_add_test, Test9) {
    history_t *history = NULL;
    history_add(&history, "ls -l");
    cr_assert_not_null(history);
    cr_assert_str_eq(history->cmd, "ls -l");
    cr_assert_eq(history->cmd_num, 1);
    cr_assert_not_null(history->time);
    cr_assert_null(history->next);
}

Test(list_to_array_test, Test10) {
    history_t *history1 = malloc(sizeof(history_t));
    history1->cmd_num = 1;
    history1->time = strdup("3 mai 2024 - 16:08");
    history1->cmd = strdup("ls -l");
    history1->next = NULL;
    history_t *history2 = malloc(sizeof(history_t));
    history2->cmd_num = 2;
    history2->time = strdup("20 janvier 2004 - 18:00");
    history2->cmd = strdup("cd Documents");
    history2->next = NULL;
    history1->next = history2;
    char **result = list_to_array(&history1);
    cr_assert_not_null(result);
    cr_assert_str_eq(result[0], "    1  3 mai 2024 - 16:08  ls -l");
    cr_assert_str_eq(result[1], "    2  20 janvier 2004 - 18:00  cd Documents");
    cr_assert_null(result[2]);
    for (int i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

Test(array_to_str_test, Test11) {
    char *input[] = {"Hello", "World", "!", NULL};
    char *result = array_to_str(input);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "Hello\nWorld\n!");
    free(result);
}
