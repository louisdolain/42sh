/*
** EPITECH PROJECT, 2023
** BASICS LIB
** File description:
** HEADER
*/

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#ifndef BASICS_H
    #define BASICS_H
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strcat(char *dest, char const *src, int u);
int my_putstr(char const *str);
int my_put_nbr(long n);
int display_var2(va_list args, char *str, int i);
int isntvar(char *str, int i);
int my_putchar(char c);
int my_atoi(char const *str, int i);
char *my_strdup(char const *str);
void *my_memcpy(void *dest, const void *source, size_t n);
void *my_realloc(void *ptr, size_t old_size, size_t new_size);
char **my_str_to_all_array(char *str, char *separators);
int str_begin_with(char *str, char *find);
void free_str_array(char **array);
char *concat_mem(char *str1, char *str2, char *str3);
int my_strcmp(char const *s1, char const *s2);
int mini_printf(char *str, ...);
int my_putstr_array(char **array);
char **my_strdup_array(char **array);
int my_strlen_array(char **array);
void my_fputstr(char const *str, int fd);
void **append_ptr(void ***ptr, void *entity, int *len);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strndup(char const *str, int n);
void *smalloc(size_t size);
void **append_ptr(void ***ptr, void *entity, int *len);
int my_arraylen(void **array);
int my_strncmp(char const *s1, char const *s2, int n);
char *cleanstr(char *str);
void overwrite_file(char *filepath, char *string);
void appendwrite_file(char *filepath, char *string);
char *open_file(char *filepath);
int contain_number(const char *str);
int is_number(char *str);

#endif
