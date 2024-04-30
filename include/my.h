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
#include "basics.h"
#include "parsing.h"
#include "bulletin.h"

#ifndef MY_H
    #define MY_H
    #define MAX_OUTPUT_SIZE 200480

    #define SEPARATOR_AND "&&"
    #define SEPARATOR_PIPE '|'

typedef struct history_s {
    int cmd_num;
    char *time;
    char *cmd;
    struct history_s *next;
} history_t;

// tools functions
char **get_bin_path_list(char **env);
void free_mysh(char *user_input, char ***env);
void free_process(char ***parsed_input, char **paths);
char **get_fct_paths(char **bin_path_list, char *function_name);
char *my_getenv(char **env, char *to_find);

//Ls function
void put_color_ls(char ***parsed_input);

//error handling
int setenv_error(char ***parsed_input);
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

// history
void free_list(history_t **list);
void print_array(char **array, char *str);
int len_list(history_t *list);
int is_num(char c);
int is_number(char *str);
char *my_get_time(void);
void display_history(history_t *list, char *flag);
void display_history_reverse(history_t **list);
void clear_history(history_t **list);
void *free_array(char **array);
char **list_to_array(history_t **list);
char *array_to_str(char **array);
void my_save(history_t **list);
void exclamation_mark(history_t **list, char *command, char ***input);
void history_add(history_t **list, char *command);


#endif
