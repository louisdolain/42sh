/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** parantheses_error
*/

#include "my.h"

static int count_occ(char *user_input, char c)
{
    int count = 0;
    bool in_quote = false;

    for (int i = 0; user_input[i]; i++) {
        if (user_input[i] == '\'' && !in_quote) {
            in_quote = true;
            continue;
        }
        if (user_input[i] == '\'' && in_quote) {
            in_quote = false;
            continue;
        }
        count += (!in_quote && user_input[i] == c);
    }
    return count;
}

bool verifiy_parantheses(char *user_input)
{
    int nb_open = count_occ(user_input, '(');
    int nb_close = count_occ(user_input, ')');

    if (nb_open > nb_close)
        my_fputstr("Too many ('s.\n", 2);
    if (nb_close > nb_open)
        my_fputstr("Too many )'s.\n", 2);
    return nb_open == nb_close;
}
