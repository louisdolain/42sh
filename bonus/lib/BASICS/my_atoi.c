/*
** EPITECH PROJECT, 2023
** mygetnbr
** File description:
** mygetnbr
*/

#include "basics.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int my_atoi(char const *str, int i)
{
    int nb = 0;
    bool in_nb = false;
    int multiplier = 1;

    for (i = i; str[i] != '\0'; i++) {
        if ((str[i] < '0' || str[i] > '9') && in_nb == true)
            break;
        if (str[i] == '-')
            multiplier *= -1;
        if (str[i] >= '0' && str[i] <= '9') {
            in_nb = true;
            nb = (nb * 10) + (str[i] - '0');
        }
    }
    return nb * multiplier;
}
