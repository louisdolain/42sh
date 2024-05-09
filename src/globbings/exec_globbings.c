/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-pierre.lissope
** File description:
** exec_globbings.c
*/
#include "globbing.h"

int check_glob(char **parsed_input, glob_t globbuf, int i)
{
    for (int j = 0; j < i; j++) {
        if (contains_globbing_pattern(parsed_input[j]))
            continue;
        globbuf.gl_pathv[j] = parsed_input[j];
    }
    return 0;
}

int count_arguments(char ***parsed_input, int num_args)
{
    while ((*parsed_input)[num_args] != NULL) {
        num_args++;
    }
    return num_args;
}
