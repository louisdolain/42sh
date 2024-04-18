/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** parse_red
*/

#include "my.h"
#include <fcntl.h>

static bool str_is_empty(char *str, int n)
{
    for (int i = 0; i < n; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
            return false;
    }
    return true;
}

static int len_until_next(char const *str)
{
    int len = 0;

    while (str[len] && str[len] != '>' && str[len] != '<')
        len++;
    return len;
}

static int get_str_after(char *str, char *string, char **entity)
{
    int len = 0;
    int lenstring = my_strlen(string);

    for (char *ptr = str; *ptr; ptr++) {
        if (my_strncmp(ptr, string, lenstring) != 0)
            continue;
        if (lenstring == 1 && (*(ptr + 1) == *ptr || *(ptr - 1) == *ptr))
            continue;
        ptr += lenstring;
        len = len_until_next(ptr);
        if (len == 0 || str_is_empty(ptr, len)) {
            my_fputstr("Missing...", 2);
            return 84;
        }
        if (*entity != NULL)
            return 84;
        *entity = my_strndup(ptr, len);
    }
    return 0;
}

static int get_redirection_files(command_t *command, redirection_t *red)
{
    if (get_str_after(command->command_line, ">",
        &red->output_file) == 84 ||
        get_str_after(command->command_line, ">>",
        &red->d_output_file) == 84) {
        my_fputstr("Ambiguous output redirect.\n", 2);
        return 84;
    }
    if (get_str_after(command->command_line, "<",
        &red->input_file) == 84 ||
        get_str_after(command->command_line, "<<",
        &red->d_input_file) == 84) {
        my_fputstr("Ambiguous input redirect.\n", 2);
        return 84;
    }
    return 0;
}

int parse_input_file(command_t *command, redirection_t *red)
{
    if (red->input_file || red->d_input_file) {
        if ((red->input_file && red->d_input_file) ||
            command->input_redirected) {
            my_fputstr("Ambiguous input redirect.\n", 2);
            return 84;
        }
        if (red->input_file)
            command->input_fd = open(red->input_file, O_RDONLY);
        if (red->d_input_file)
            command->input_fd = open(red->d_input_file, O_RDONLY);
        command->input_redirected = 1;
    }
    return 0;
}

int parse_output_file(command_t *command, redirection_t *red)
{
    if (red->output_file || red->d_output_file) {
        if ((red->output_file && red->d_output_file) ||
            command->output_redirected) {
            my_fputstr("Ambiguous output redirect.\n", 2);
            return 84;
        }
        if (red->output_file)
            command->output_fd = open(red->output_file,
                O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (red->d_output_file)
            command->output_fd = open(red->d_output_file,
                O_WRONLY | O_CREAT | O_APPEND, 0644);
        command->output_redirected = 1;
    }
    return 0;
}

int parse_redirection(command_t *command, redirection_t *red)
{
    if (get_redirection_files(command, red) == 84)
        return 84;
    command->command = my_strndup(command->command_line,
        len_until_next(command->command_line));
    red->d_input_file = cleanstr(red->d_input_file);
    red->d_output_file = cleanstr(red->d_output_file);
    red->input_file = cleanstr(red->input_file);
    red->output_file = cleanstr(red->output_file);
    if (parse_input_file(command, red) == 84 ||
        parse_output_file(command, red) == 84)
        return 84;
    free(red->d_input_file);
    free(red->d_output_file);
    free(red->input_file);
    free(red->output_file);
    return 0;
}
