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

int handle_globbing(char *cmd, char **parsed_input,
    char **paths, char ***env)
{
    glob_t globbuf;
    size_t nbr_bfr_glob = nbr_wdr(cmd);
    int i = 0;

    globbuf.gl_offs = 1;
    while (parsed_input[i]) {
        glob(parsed_input[i], GLOB_DOOFFS |
            (i == 0 ? 0 : GLOB_APPEND), NULL, &globbuf);
        i++;
    }
    if (globbuf.gl_pathc == 0) {
        printf("Aucun fichier trouvé avec le motif donné.\n");
        globfree(&globbuf);
        return -1;
    }
    check_glob(parsed_input, globbuf, i);
    exec_cmd(globbuf.gl_pathv, paths, env);
    return 0;
}
