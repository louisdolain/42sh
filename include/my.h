/*
** EPITECH PROJECT, 2023
** header
** File description:
** my.h
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>
#include <glob.h>
#include <sys/stat.h>
#include "basics.h"
#include "parsing.h"
#include "globbing.h"

#ifndef MY_H
    #define MY_H
    #define MAX_OUTPUT_SIZE 200480

    #define SEPARATOR_AND "&&"
    #define SEPARATOR_PIPE '|'

// tools functions
char **get_bin_path_list(char **env);
void free_mysh(char *user_input, char ***env);
void free_process(char **parsed_input, char **paths);
char **get_fct_paths(char **bin_path_list, char *function_name);
char *my_getenv(char **env, char *to_find);

//Ls function
void put_color_ls(char ***parsed_input);

//error handling
int setenv_error(char **parsed_input);
void replace_endline(char *user_input);
void write_error_cd(char *command);
void execve_error(char *command);

//env management
void fill_env(char ***env);

//bulletin
int my_exit(char *userinput, int *exit);

char *handle_backticks(char *user_input, char ***env);
int recursive_compute(token_t *token, char ***env);
int redirect_tokens(token_t *token);
void parse_token_redirections(token_t *token);
bool verifiy_parantheses(char *user_input);
#endif
