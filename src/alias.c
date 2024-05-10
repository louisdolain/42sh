/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** alias
*/

#include "../include/my.h"
#include "../include/alias.h"

static int is_an_alias(char *str, alias_t **alias_list)
{
    int i = 0;

    while (alias_list != NULL && alias_list[i] != NULL) {
        if (strcmp(alias_list[i]->alias, str) == 0)
            return i;
        i++;
    }
    return -1;
}

int replace_alias(char **parsed_input, alias_t **alias_list)
{
    int alias_index = -1;


    for (int i = 0; parsed_input[i] != NULL; i++) {
        alias_index = is_an_alias(parsed_input[i], alias_list);
        printf("%s\n", parsed_input[i]);
        if (alias_index != -1) {
            free(parsed_input[i]);
            parsed_input[i] = strdup(alias_list[alias_index]->command);
        }
    }
    return 0;
}

static int add_command_from_input(char **parsed_input, alias_t *new_alias)
{
    new_alias->command = strdup(parsed_input[2]);
    for (int i = 3; parsed_input[i] != NULL; i++) {
        new_alias->command = realloc(new_alias->command,
            sizeof(char) * (strlen(new_alias->command) +
            strlen(parsed_input[i]) + 1));
        sprintf(new_alias->command,
        "%s %s", new_alias->command, parsed_input[i]);
    }
    return 0;
}

int process_alias(char **parsed_input, alias_t ***alias_list)
{
    alias_t *new_alias = malloc(sizeof(alias_t));

    if (parsed_input[1] == NULL)
        return 0;
    new_alias->alias = parsed_input[1];
    add_command_from_input(parsed_input, new_alias);

    append_ptr((void ***)alias_list, new_alias, NULL);
    return 0;
}
