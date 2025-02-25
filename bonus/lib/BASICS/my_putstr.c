/*
** EPITECH PROJECT, 2023
** pr1
** File description:
** my_print_alpha
*/

#include <unistd.h>
#include "basics.h"

int my_putchar(char c)
{
    write(1, &c, 1);
    return 0;
}

int my_putstr(char const *str)
{
    write(1, str, my_strlen(str));
    return 0;
}

void my_fputstr(char const *str, int fd)
{
    write(fd, str, my_strlen(str));
}

int my_putstr_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        mini_printf("%s", array[i]);
        if (array[i][0] != '\0')
            my_putchar('\n');
    }
    return 0;
}
