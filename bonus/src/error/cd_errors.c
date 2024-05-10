/*
** EPITECH PROJECT, 2023
** process
** File description:
** process.c
*/

#include "my.h"

void write_error_cd(char *command)
{
    if (errno == EACCES) {
        my_fputstr(command, 2);
        my_fputstr(": Permission denied.\n", 2);
    }
    if (errno == ENOTDIR) {
        my_fputstr(command, 2);
        my_fputstr(": Not a directory.\n", 2);
    }
    if (errno == ENOENT) {
        my_fputstr(command, 2);
        my_fputstr(": No such file or directory.\n", 2);
    }
}
