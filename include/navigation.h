/*
** EPITECH PROJECT, 2024
** line navigation
** File description:
** header
*/

#ifndef NAVIGATION_H_
    #define NAVIGATION_H_
    #define MAX_INPUT_LENGTH 1000
    #define MAX_HISTORY_SIZE 100

    #include <termios.h>

typedef struct history_s {
    char *history[MAX_HISTORY_SIZE];
    int history_size;
    int current_history_index;
} line_history_t;

typedef struct input_s {
    char *input;
    int *cursor_pos;
    int *input_length;
    line_history_t *hist;
    char c;
} input_t;

//handle_keys.c
void handle_printable(char *input, int *cursor_pos,
    int *input_length, char c);
void handle_backspace(char *input, int *cursor_pos,
    int *input_length);
void handle_delete(char *input, int *cursor_pos, int *input_length);

//print.c
void print_prompt(const char *prompt);
void print_exit_message(void);
void print_input(char *input, int cursor_pos, int input_length);

//handle_user_input.c
int handle_user_input_loop(char *input, int *cursor_pos,
    int *input_length, line_history_t *hist);
int input_not_empty(char *user_input);
int process_user_input(input_t *input_data);

//terminal_setup.c
void set_terminal_mode(struct termios *old_rules, struct termios *new_rules);

//up_down_arrows.c
line_history_t *initialize_history(void);
void cleanup_history(line_history_t *hist);
void add_to_history(line_history_t *hist, const char *input);
void handle_down_arrow(input_t *input_data);
void handle_up_arrow(input_t *input_data);

//handle_keys.c
void handle_rest(input_t *input_data, char c);

//handle_arrow_key.c
void handle_arrow_key(input_t *input_data, char c);

//left_right_arrows.c
void handle_left_arrow(int *cursor_pos);
void handle_right_arrow(char *input, int *cursor_pos, int *input_length);

#endif /* NAVIGATION_H_ */
