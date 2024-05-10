/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** alias
*/

#include "my.h"
#include "alias.h"

int process_alias(char **parsed_input, alias_t ***alias_list)
{
    alias_t *new_alias = malloc(sizeof(alias_t));

    if (parsed_input[1] == NULL)
        return 0;
    new_alias->alias = parsed_input[1];
    printf("alias : %s\n", new_alias->alias);
    //my_strcat(new_alias.command, );

    printf("alias list : >%p<\n", *alias_list);
    append_ptr((void ***)alias_list, new_alias, NULL);
    for (int i = 0; alias_list != NULL && alias_list[i] != NULL; i++)
        printf("alias n°%i : >%p<\n", i, alias_list[i]);
    return 0;
}
