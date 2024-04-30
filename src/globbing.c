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

static int execute_command(char *cmd, char **arg)
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

int contains_globbing_pattern(const char *str)
{
    return strchr(str, '*') != NULL || strchr(str, '?') != NULL
        || strchr(str, '[') != NULL;
}

int handle_globbing(char *cmd, char *line)
{
    glob_t globbuf;
    size_t nbr_bfr_glob = nbr_wdr(line);
    char **arg = NULL;
    int i = 0;

    arg = my_str_to_all_array(cmd, " ");
    globbuf.gl_offs = nbr_bfr_glob;
    while (arg[i]) {
        glob(arg[i], GLOB_DOOFFS | (i == 0 ? 0 : GLOB_APPEND), NULL, &globbuf);
        i++;
    }
    for (int j = 0; j < i; j++) {
        if (contains_globbing_pattern(arg[j]))
            continue;
        globbuf.gl_pathv[j] = arg[j];
    }
    execute_command(line, globbuf.gl_pathv);
    return 0;
}
