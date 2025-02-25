/*
** EPITECH PROJECT, 2023
** pr1
** File description:
** my_print_alpha
*/

#include "basics.h"

void printmax(void)
{
    my_putchar('2');
    my_putchar('1');
    my_putchar('4');
    my_putchar('7');
    my_putchar('4');
    my_putchar('8');
    my_putchar('3');
    my_putchar('6');
    my_putchar('4');
}

void nextfct(long n)
{
    if (n < 0 && n != -2147483648) {
        my_putchar('-');
        n = n * -1;
    }
    if (n <= 9) {
        my_putchar(n + 48);
    }
    if (n >= 10) {
        my_put_nbr(n / 10);
        my_put_nbr(n % 10);
    }
}

int my_put_nbr(long n)
{
    if (n == 2147483647) {
        printmax();
        my_putchar('7');
        return 1;
    }
    if (n == -2147483648) {
        my_putchar('-');
        printmax();
        my_putchar('8');
        return 1;
    }
    nextfct(n);
    return 0;
}
