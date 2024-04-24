/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-pierre.lissope
** File description:
** globbing.c
*/
#include <glob.h>
#include <sys/stat.h>
#include "include/my.h"

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

int exec_vp(char *cmd, char **arg)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;
    } else if (pid == 0) {
        execvp(cmd, arg);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid, NULL, 0);
    }
    return 0;
}

int handle_globbing(char *cmd, char *line)
{
    glob_t globbuf;
    size_t nbr_bfr_glob = nbr_wdr(line);
    char **arg = NULL;
    int i = 0;

    arg = str_to_word_array(' ', line);
    globbuf.gl_offs = nbr_bfr_glob;
    while (arg[i]) {
        glob(arg[i], GLOB_DOOFFS | (i == 0 ? 0 : GLOB_APPEND), NULL, &globbuf);
        i++;
    }
    globbuf.gl_pathv[0] = cmd;
    for (int j = 0; j < i; j++) {
        globbuf.gl_pathv[j] = arg[j];
    }
    exec_vp(cmd, globbuf.gl_pathv);
    return 0;
}
