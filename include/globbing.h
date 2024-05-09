/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-pierre.lissope
** File description:
** glob.h
*/

#pragma once

#include <glob.h>
#include <string.h>

size_t nbr_wdr(const char *str);
int count_arguments(char ***parsed_input, int num_args);
int contains_globbing_pattern(const char *str);
int check_glob(char **parsed_input, glob_t globbuf, int i);
