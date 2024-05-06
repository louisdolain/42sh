/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-pierre.lissope
** File description:
** globbing.c
*/

#include "my.h"
#include "globbing.h"

size_t nbr_wdr(const char *str)
{
    int count = 0;
    int in_word = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            in_word = 0;
        }
        if (str[i] == '*' || str[i] == '?' || str[i] == '[') {
            break;
        }
        if (!in_word && str[i] != ' ') {
            in_word = 1;
            count++;
        }
    }
    return count;
}

int contains_globbing_pattern(const char *str)
{
    return strchr(str, '*') != NULL || strchr(str, '?') != NULL
        || strchr(str, '[') != NULL;
}

int handle_globbing(char *cmd, char **parsed_input,
    char **paths, char ***env)
{
    glob_t globbuf;
    size_t nbr_bfr_glob = nbr_wdr(cmd);
    int i = 0;

    globbuf.gl_offs = nbr_bfr_glob;
    while (parsed_input[i]) {
        glob(parsed_input[i], GLOB_DOOFFS |
            (i == 0 ? 0 : GLOB_APPEND), NULL, &globbuf);
        i++;
    }
    for (int j = 0; j < i; j++) {
        if (contains_globbing_pattern(parsed_input[j]))
            continue;
        globbuf.gl_pathv[j] = parsed_input[j];
    }
    exec_cmd(&globbuf.gl_pathv, paths, env);
    return 0;
}
