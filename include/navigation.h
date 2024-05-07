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

typedef struct history_s {
    char *history[MAX_HISTORY_SIZE];
    int history_size;
    int current_history_index;
} history_t;

typedef struct input_s {
    char *input;
    int *cursor_pos;
    int *input_length;
    history_t *hist;
} input_t;

//print.c
void print_prompt(const char *prompt);
void print_exit_message(void);
void print_input(char *input, int cursor_pos, int input_length);

//handle_user_input.c
int handle_user_input_loop(char *input, int *cursor_pos,
			   int *input_length, history_t *hist);
int input_not_empty(char *user_input);

//up_down_arrows.c
history_t *initialize_history(void);
void cleanup_history(history_t *hist);
void add_to_history(history_t *hist, const char *input);
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
