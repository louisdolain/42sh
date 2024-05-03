/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** unit_tests
*/

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <string.h>
#include "my.h"

void display_tokens(token_t *tokens, int indent, char *string) {
    char temp[100000];

    for (int i = 0; i < indent; i++)
        strcat(string, "--");
    sprintf(temp, "%s in: %d, out: %d\n\n", tokens->content,
        tokens->input_fd, tokens->output_fd);
    strcat(string, temp);
    if (tokens->under_tokens) {
        display_tokens(tokens->under_tokens[0], indent + 1, string);
        display_tokens(tokens->under_tokens[1], indent + 1, string);
    }
}

Test(Parser, Test1) {
    token_t *token = calloc(1, sizeof(token_t));
    char string[100000];

    token->content = strdup("(((ls -l ; echo Hello) | cat -e) | grep lib)");
    token->input_fd = -1;
    token->output_fd = -1;
    ll_parser(token);
    display_tokens(token, 0, string);
    cr_assert_str_eq(open_file("tests/parsing/test1"), string);
}

Test(Parser, Test2)
{
    token_t *token = calloc(1, sizeof(token_t));
    char string[100000];

    token->content = strdup("((ls -l ; cat < Makefile; echo Hello) | cat -e ; cat Makefile) | grep lib ; cat src/main.c");
    token->input_fd = -1;
    token->output_fd = -1;
    ll_parser(token);
    display_tokens(token, 0, string);
    cr_assert_str_eq(open_file("tests/parsing/test2"), string);
}

Test(Parser, Test3) {
    token_t *token = calloc(1, sizeof(token_t));
    char string[100000];

    token->content = strdup("((ls -l ; cat < Makefile; echo Bonjour) | cat -e | cat -e; cat < Makefile) | grep lib ; cat src/main.c");
    token->input_fd = -1;
    token->output_fd = -1;
    ll_parser(token);
    display_tokens(token, 0, string);
    cr_assert_str_eq(open_file("tests/parsing/test3"), string);
}

Test(Parser, Test4) {
    token_t *token = calloc(1, sizeof(token_t));
    char string[100000];

    token->content = strdup("(((ls -l ; echo Hello) | cat -e) | grep lib | grep test)");
    token->input_fd = -1;
    token->output_fd = -1;
    ll_parser(token);
    display_tokens(token, 0, string);
    cr_assert_str_eq(open_file("tests/parsing/test4"), string);
}

Test(Parser, Test5) {
    token_t *token = calloc(1, sizeof(token_t));
    char string[100000];

    token->content = strdup("((ls -l ; echo Hello | cat -e) | grep lib | grep test)");
    token->input_fd = -1;
    token->output_fd = -1;
    ll_parser(token);
    display_tokens(token, 0, string);
    cr_assert_str_eq(open_file("tests/parsing/test5"), string);
}

Test(Parser, Test6) {
    token_t *token = calloc(1, sizeof(token_t));
    char string[100000];

    token->content = strdup("((echo 'hello je suis un test';ls ; echo Hello | cat -e) | grep lib | grep test)");
    token->input_fd = -1;
    token->output_fd = -1;
    ll_parser(token);
    display_tokens(token, 0, string);
    cr_assert_str_eq(open_file("tests/parsing/test6"), string);
}

Test(Parser, Test7) {
    token_t *token = calloc(1, sizeof(token_t));
    char string[100000];

    token->content = strdup("((ls -l ; cat < Makefile; echo Bonjour) | cat -e | cat -e; cat < Makefile) | grep lib ; cat Makefile");
    token->input_fd = -1;
    token->output_fd = -1;
    ll_parser(token);
    display_tokens(token, 0, string);
    cr_assert_str_eq(open_file("tests/parsing/test7"), string);
}
