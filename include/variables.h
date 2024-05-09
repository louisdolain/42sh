/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** variables
*/

#ifndef VARIABLES_H_
    #define VARIABLES_H_

typedef struct variable_s {
    char *first;
    char *second;
    struct variable_s *next;
} variable_t;

char *find_local(variable_t **list, char *command);
void add_local(variable_t **list, char ***parsed_input);
void remove_local(variable_t **list, char *parsed_input);
char *find_local(variable_t **list, char *command);
void print_term(char ***env);
void print_cwd(void);
char *var_finder(char **env, char *to_find);

#endif /* !VARIABLES_H_ */
