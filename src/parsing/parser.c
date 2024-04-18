/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** parser
*/

#include "my.h"

static char *get_separator(char *user_input)
{
    if (*user_input == ';')
        return ";";
    if (*user_input == SEPARATOR_AND[0] &&
        *(user_input + 1) == SEPARATOR_AND[1])
        return "&&";
    if (*user_input == SEPARATOR_PIPE)
        return "|";
    return NULL;
}

static int len_next_command(char *user_input)
{
    int len = 0;

    while (*user_input &&
        !get_separator(user_input)) {
        len++;
        user_input++;
    }
    return len;
}

static command_t *init_enity(char **user_input, int len)
{
    command_t *entity = malloc(sizeof(command_t));

    entity->command_line = my_strndup(*user_input, len);
    (*user_input) += len;
    entity->nextflag = get_separator(*user_input);
    entity->input_fd = -1;
    entity->output_fd = -1;
    entity->command = NULL;
    if (entity->nextflag && !my_strcmp(entity->nextflag, "&&"))
        (*user_input) += 2;
    return entity;
}

static void manage_redirection(command_t **array, int i)
{
    if (array[i]->nextflag && !my_strcmp(array[i]->nextflag, "|")) {
        array[i]->output_redirected = 1;
        array[i + 1]->input_redirected = 1;
    } else {
        array[i]->output_redirected = 0;
        if (array[i + 1])
            array[i + 1]->input_redirected = 0;
    }
}

static int config_array(command_t **array)
{
    for (int i = 0; array && array[i]; i++) {
        if (i == 0)
            array[i]->input_redirected = 0;
        if (array[i]->nextflag &&
            (!my_strcmp(array[i]->nextflag, "|") ||
            !my_strcmp(array[i]->nextflag, "&&")) &&
            !array[i + 1]) {
            my_fputstr("Invalid null command.\n", 2);
            return 1;
        }
        manage_redirection(array, i);
    }
    return 0;
}

static int first_is_sep(char *user_input)
{
    char **input_array = my_str_to_all_array(user_input, " \t");
    char *seps[] = {"&&", "|", NULL};

    for (int i = 0; seps[i]; i++) {
        if (!my_strcmp(seps[i], input_array[0])) {
            free_str_array(input_array);
            return 1;
        }
    }
    free_str_array(input_array);
    return 0;
}

void destroy_command_array(command_t **command_array)
{
    for (int i = 0; command_array &&
        command_array[i]; i++) {
        free(command_array[i]->command);
        free(command_array[i]->command_line);
        free(command_array[i]);
    }
    free(command_array);
}

command_t **get_command_array(char *user_input)
{
    command_t **array = NULL;
    command_t *entity = NULL;
    int len = 0;

    if (first_is_sep(user_input))
        return NULL;
    while (*user_input) {
        len = len_next_command(user_input);
        if (len != 0) {
            entity = init_enity(&user_input, len);
            append_ptr((void ***)&array, entity, NULL);
        } else
            user_input++;
    }
    if (config_array(array) == 1) {
        destroy_command_array(array);
        return NULL;
    }
    return array;
}
