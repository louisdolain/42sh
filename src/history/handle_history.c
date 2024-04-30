/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** handle_history
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bulletin.h"
#include "my.h"


void print_array(char **array, char *str){
    printf("%s \n", str);
    for (int i = 0; array[i] != 0; i++)
        printf("%s\n", array[i]);
}

void process_history(char ***parsed_input, char ***env, int *res, history_t **list)
{
    if ((*parsed_input)[0][0] == '!')
        return exclamation_mark(list, (*parsed_input)[0], parsed_input);
    if (my_strcmp((*parsed_input)[0], "history") == 0) {
        if (my_strcmp((*parsed_input)[1], "-h") == 0)
            return display_history(*list, "-h");
        if (my_strcmp((*parsed_input)[1], "-c") == 0)
            return clear_history(list);
        if (my_strcmp((*parsed_input)[1], "-r") == 0)
            return display_history_reverse(list);
        if (my_strcmp((*parsed_input)[1], "-s") == 0)
            return my_save(list);
        if (my_strcmp((*parsed_input)[0], "history") == 0)
            return display_history(*list, "");
    }
}
