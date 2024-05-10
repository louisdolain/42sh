/*
** EPITECH PROJECT, 2023
** lib
** File description:
** myh
*/

#include "basics.h"

int get_nb_len(int nb)
{
    int count = 0;

    if (nb == 0)
        return 1;
    while (nb != 0) {
        count++;
        nb /= 10;
    }
    return count;
}

char *my_itoa(int nb)
{
    int len = get_nb_len(nb);
    char *str = malloc(sizeof(char) * (len + 1));

    if (nb == 0) {
        str[0] = '0';
        str[1] = '\0';
    }
    for (int i = len - 1; i >= 0; i--) {
        str[i] = (nb % 10) + '0';
        nb /= 10;
    }
    str[len] = '\0';
    return str;
}
