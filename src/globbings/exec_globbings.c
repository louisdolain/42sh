/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-pierre.lissope
** File description:
** exec_globbings.c
*/
#include "my.h"
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

int handle_globbing(char ***parsed_input,
    char **paths, char ***env)
{
    glob_t globbuf;
    int i = 0;
    int num_args = 0;

    num_args = count_arguments(parsed_input, num_args);
    if (num_args == 1)
        return -1;
    globbuf.gl_offs = 1;
    while ((*parsed_input)[i]) {
        glob((*parsed_input)[i], GLOB_DOOFFS |
            (i == 0 ? 0 : GLOB_APPEND), NULL, &globbuf);
        i++;
    }
    if (globbuf.gl_pathc == 0) {
        globfree(&globbuf);
        return -1;
    }
    check_glob((*parsed_input), globbuf, i);
    return exec_cmd(&globbuf.gl_pathv, paths, env);
}
