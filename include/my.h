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

#ifndef MY_H
    #define MY_H
    #define MAX_OUTPUT_SIZE 200480

    #define SEPARATOR_AND "&&"
    #define SEPARATOR_PIPE '|'

typedef enum fd_state_e {
    INPUT_REDIRECTION = -2,
    OUTPUT_REDIRECTION = -3,
} fd_state_t;

typedef struct command_s {
    char *command_line;
    char *command;
    char *nextflag;
    int input_redirected;
    int output_redirected;
    int input_fd;
    int output_fd;
    int pipe_in[2];
    int pipe_out[2];
} command_t;

typedef struct redirection_s {
    char *d_output_file;
    char *d_input_file;
    char *output_file;
    char *input_file;
} redirection_t;

typedef struct token_s {
    char *content;
    char *command;
    char *separator;
    struct token_s **under_tokens;
    int input_redirected;
    int output_redirected;
    int input_fd;
    int output_fd;
    char *input_file;
    char *output_file;
} token_t;

// tools functions
char **get_bin_path_list(char **env);
void free_mysh(char *user_input, char ***env);
void free_process(char **parsed_input, char **paths);
char **get_fct_paths(char **bin_path_list, char *function_name);
char *my_getenv(char **env, char *to_find);

// process functions
int process_parent(__pid_t pid, char **parsed_input,
    char **paths, char ***env);
int process_setenv(char **parsed_input, char ***env);
int process_multiple_command(char *command_line, char ***env);
int recursive_process(command_t **command_array, char ***env);

//Specific functions
void process_cd(char **parsed_input, char ***env, int *res);
void process_env(char **parsed_input, char ***env, int *res);
void process_segfault(int status, int *res);

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

// Parsing functions
void destroy_command_array(command_t **command_array);
int parse_redirection(token_t *token, redirection_t *red);
void remove_outer_parentheses(char *content_ptr);
token_t *ll_parser(token_t *head);
int redirect_tokens(token_t *token);
#endif
