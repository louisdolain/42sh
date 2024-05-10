/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** alias
*/

#ifndef ALIAS_H_
    #define ALIAS_H_

    typedef struct alias_s {
        char *alias;
        char *command;
    }alias_t;

int process_alias(char **parsed_input, alias_t ***alias_list);
int replace_alias(char **parsed_input, alias_t **alias_list);

#endif /* !ALIAS_H_ */
