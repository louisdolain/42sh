/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** execve_errors
*/

#include "my.h"

void execve_error(char *command)
{
    if (errno == ENOENT)
        return;
    if (errno == EACCES) {
        my_fputstr(command, 2);
        my_fputstr(": Permission denied.\n", 2);
    }
    if (errno == ENOEXEC) {
        my_fputstr(command, 2);
        my_fputstr(": Exec format error. Wrong Architecture.\n", 2);
    }
    exit(1);
}
