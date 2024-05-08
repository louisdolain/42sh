/*
** EPITECH PROJECT, 2024
** terminal_setup
** File description:
** 42sh
*/
#include "navigation.h"
#include <termios.h>
#include <unistd.h>
#include <string.h>

void set_terminal_mode(struct termios *old_rules, struct termios *new_rules)
{
    memset(old_rules, 0, sizeof(struct termios));
    memset(new_rules, 0, sizeof(struct termios));
    tcgetattr(STDIN_FILENO, old_rules);
    *new_rules = *old_rules;
    new_rules->c_lflag &= ~ICANON;
    new_rules->c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, new_rules);
}
