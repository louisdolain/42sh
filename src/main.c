/*
** EPITECH PROJECT, 2023
** main
** File description:
** main.c
*/
#include "my.h"
#include "process.h"
#include "navigation.h"
#include <termios.h>

int get_user_input(char **user_input,  history_t *hist)
{
    struct termios old_rules;
    struct termios new_rules;
    char *input = calloc(MAX_INPUT_LENGTH, sizeof(char));
    int cursor_pos = 0;
    int input_length = 0;
    int result = 0;

    set_terminal_mode(&old_rules, &new_rules);
    result = handle_user_input_loop(input, &cursor_pos, &input_length, hist);
    if (isatty(STDIN_FILENO))
        printf("\n");    
    *user_input = strdup(input);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_rules);
    free(input);
    if (result == EOF)
        return EOF;
    return strlen(*user_input);
}

int mysh(char ***env)
{
    char *user_input = NULL;
    int exit = 0;
    history_t *hist = initialize_history();

    while (get_user_input(&user_input, hist) != EOF) {
        if (!input_not_empty(user_input))
            continue;
        replace_endline(user_input);
        if (my_exit(user_input, &exit))
            break;
        fill_env(env);
        exit = process_multiple_command(user_input, env);
        free(user_input);
        user_input = NULL;
    }
    cleanup_history(hist);
    print_exit_message();
    return exit;
}

char **create_env(void)
{
    char **env = calloc(6, sizeof(char *));
    char pwd[2048];

    getcwd(pwd, 2048);
    env[0] = concat_mem("PWD", "=", pwd);
    env[1] = concat_mem("OLDPWD", "=", pwd);
    env[2] = concat_mem("HOME", "=", "/home");
    env[3] = concat_mem("PATH", "=", "");
    env[4] = concat_mem("TERM", "=", "xterm-256color");
    return env;
}

int main(int ac, char **av, char **env)
{
    char **envcpy = NULL;

    if (env[0] != NULL)
        envcpy = my_strdup_array(env);
    else
        envcpy = create_env();
    if (ac != 1 || av[1] != NULL) {
        free_str_array(envcpy);
        return 84;
    }
    return mysh(&envcpy);
}
