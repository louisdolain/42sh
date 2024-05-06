/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-pierre.lissope
** File description:
** exec_globbings.c
*/
#include "my.h"
#include "globbing.h"

int handle_globbing(char *cmd, char **parsed_input,
    char **paths, char ***env)
{
    glob_t globbuf;
    size_t nbr_bfr_glob = nbr_wdr(cmd);
    int i = 0;

    globbuf.gl_offs = nbr_bfr_glob;
    while (parsed_input[i]) {
        glob(parsed_input[i], GLOB_DOOFFS | GLOB_TILDE_CHECK | GLOB_MARK |
            (i == 0 ? 0 : GLOB_APPEND), NULL, &globbuf);
        i++;
    }
    for (int j = 0; j < i; j++) {
        if (contains_globbing_pattern(parsed_input[j]))
            continue;
        globbuf.gl_pathv[j] = parsed_input[j];
    }
    exec_cmd(globbuf.gl_pathv, paths, env);
    return 0;
}
