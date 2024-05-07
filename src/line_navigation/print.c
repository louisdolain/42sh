/*
** EPITECH PROJECT, 2024
** print messages
** File description:
** 42sh
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "my.h"

void print_exit_message(void)
{
    if (isatty(0))
        printf("exit\n");
}

void print_input(char *input, int cursor_pos, int input_length)
{
    printf("\r\033[K");
    if (isatty(STDIN_FILENO))
        printf("\r42sh %s", input);
    for (int i = 0; i < input_length - cursor_pos; i++) {
        printf("\b");
    }
    fflush(stdout);
}
