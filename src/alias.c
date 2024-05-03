/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** alias
*/

#include "my.h"
#include "alias.h"

int process_alias(char **parsed_input, alias_t *alias_list)
{
    alias_t new_alias = {parsed_input[1], "\0"};

    //printf("arg 1 : %s\n", parsed_input[1]);
    //printf("alias : %s\n", new_alias.alias);

    for (int i = 0; parsed_input[i] != NULL; i++) {
        printf("arg 1 : %s\n", parsed_input[i]);
    }
    //my_strcat(new_alias.command, );

    //alias_list = append(alias_list, new_alias);
    return 0;
}
