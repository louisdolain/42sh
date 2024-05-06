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
int handle_globbing(char *cmd, char **parsed_input, char **paths, char ***env);
int contains_globbing_pattern(const char *str);
int exec_cmd(char ***parsed_input, char **paths, char ***env);
