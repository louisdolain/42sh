/*
** EPITECH PROJECT, 2023
** tools
** File description:
** tools.c
*/

#include "my.h"
extern history_t *list;

char **get_bin_path_list(char **env)
{
    char *pathline = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        if (str_begin_with(env[i], "PATH")) {
            pathline = env[i];
            break;
        }
    }
    if (pathline == NULL)
        return NULL;
    return my_str_to_all_array(pathline + 5, ":");
}

void free_mysh(char *user_input, config_t *config)
{
    free(user_input);
    free_str_array(config->env);
    free_list(&list);
}

void free_process(char ***parsed_input, char **paths)
{
    free_str_array((*parsed_input));
    free_str_array(paths);
}

char *my_getenv(char **env, char *to_find)
{
    for (int i = 0; env[i] != NULL; i++)
        if (str_begin_with(env[i], to_find))
            return env[i];
    return NULL;
}

char **get_fct_paths(char **bin_path_list, char *function_name)
{
    char **paths;
    int sz = 0;

    if (bin_path_list == NULL)
        return NULL;
    while (bin_path_list[sz] != NULL)
        sz++;
    paths = malloc(sizeof(char *) * (sz + 1));
    for (int i = 0; bin_path_list[i] != NULL; i++)
        paths[i] = concat_mem(bin_path_list[i], "/", function_name);
    paths[sz] = NULL;
    return paths;
}
