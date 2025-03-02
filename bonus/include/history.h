/*
** EPITECH PROJECT, 2024
** 42sh3
** File description:
** history
*/

#ifndef HISTORY_H_
    #define HISTORY_H_


typedef struct history_s {
    int cmd_num;
    char *time;
    char *cmd;
    struct history_s *next;
} history_t;

// history
int contain_number(const char *str);
int is_number(char *str);
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
char *find_by_command_prefix(history_t **list, char *command);
char *find_by_command_number(history_t **list, int number);
char *find(history_t **list, char *command);
void replace_array(char ***old_array, char **new_array);

#endif /* !HISTORY_H_ */
