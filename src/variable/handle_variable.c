/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** handle_variable
*/

#include "bulletin.h"
#include "basics.h"
#include "my.h"
#include "variables.h"

static void print_term(char ***env)
{
    char *temp = my_getenv(*env, "TERM") + 5;

    if (!temp)
        return;
    printf("%s\n", temp);
    return;
}

static void print_cwd(void)
{
    char *pwd = malloc(sizeof(char) * 2048);

    getcwd(pwd, 2048);
    printf("%s\n", pwd);
    free(pwd);
}

static void add_local(variable_t **list, char ***parsed_input)
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

static void remove_local(variable_t **list, char *parsed_input)
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

static char *find_local(variable_t **list, char *command)
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

void process_variable(char ***parsed_input, char ***env,
    int *res, history_t **list)
{
    static variable_t *var = NULL;
    char *temp = NULL;

    if (my_strcmp((*parsed_input)[0], "set") == 0) {
        add_local(&var, parsed_input);
        return;
    }
    if (my_strcmp((*parsed_input)[0], "unset") == 0) {
        remove_local(&var, (*parsed_input)[1]);
        return;
    }
    if (my_strcmp((*parsed_input)[0], "echo") == 0) {
        if (my_strcmp((*parsed_input)[1], "$term") == 0)
            return print_term(env);
        if (my_strcmp((*parsed_input)[1], "$cwd") == 0)
            return print_cwd();
        temp = find_local(&var, (*parsed_input)[1]);
        if (temp != NULL)
            printf("%s\n", temp);
    }
}
