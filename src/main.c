/*
** EPITECH PROJECT, 2023
** main
** File description:
** main.c
*/

#include "my.h"
#include "process.h"

int input_not_empty(char *user_input)
{
    if (my_strlen(user_input) < 2)
        return 0;
    for (int i = 0; user_input[i] != '\0'; i++) {
        if (user_input[i] != '\n' && user_input[i] != ' ' &&
            user_input[i] != '\t')
            return 1;
    }
    return 0;
}

int get_user_input(char **user_input, int exit)
{
    size_t byteread = 0;
    char pwd[2048];
    char **directories = NULL;
    int last = 0;
    char *dir = NULL;

    getcwd(pwd, 2048);
    directories = my_str_to_all_array(pwd, "/");
    last = my_strlen_array(directories);
    if (last == 0)
        dir = "/";
    else
        dir = directories[last - 1];
    if (isatty(0) && exit == 0)
        mini_printf("%s ", dir);
    if (isatty(0) && exit != 0)
        mini_printf("%s ", dir);
    free_str_array(directories);
    return getline(user_input, &byteread, stdin);
}

int mysh(char ***env)
{
    char *user_input = NULL;
    int exit = 0;
    int end = 0;

    while (1) {
        end = get_user_input(&user_input, exit);
        if (end == EOF)
            break;
        if (!input_not_empty(user_input))
            continue;
        replace_endline(user_input);
        if (my_exit(user_input, &exit))
            break;
        fill_env(env);
        exit = process_multiple_command(user_input, env);
    }
    if (isatty(0))
        mini_printf("exit\n");
    free_mysh(user_input, env);
    return exit;
}

char **create_env(void)
{
    char **env = malloc(sizeof(char *) * 6);
    char pwd[2048];

    getcwd(pwd, 2048);
    env[5] = NULL;
    env[0] = concat_mem("PWD", "=", pwd);
    env[1] = concat_mem("OLDPWD", "=", pwd);
    env[2] = concat_mem("HOME", "=", "/home");
    env[3] = concat_mem("PATH", "=",
        "");
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
