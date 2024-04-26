/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** unit_tests
*/

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include "my.h"


// Test(Parser, single_command_no_redirection) {
    // token_t *token = calloc(1, sizeof(token_t));
// 
    // token->content = strdup("(((ls -l ; echo Hello) | cat -e) | grep lib)");
    // token->input_fd = -1;
    // token->output_fd = -1;
    // ll_parser(token);
// 
    // cr_assert(strcmp(token->under_tokens[0]->content, " (ls -l ; echo Hello) | cat -e  ") == 0);
    // cr_assert(strcmp(token->under_tokens[0]->under_tokens[0]->content, "  ls -l ; echo Hello  ") == 0);
    // cr_assert(strcmp(token->under_tokens[0]->under_tokens[0]->under_tokens[0]->content, "  ls -l ") == 0);
    // cr_assert(strcmp(token->under_tokens[0]->under_tokens[0]->under_tokens[1]->content, " echo Hello  ") == 0);
    // cr_assert(strcmp(token->under_tokens[0]->under_tokens[1]->content, " cat -e  ") == 0);
    // cr_assert(strcmp(token->under_tokens[1]->content, " grep lib") == 0);
// }

void display_tokens(token_t *tokens, int indent)
{
    for (int i = 0; i < indent; i++)
        printf("--");
    printf("%s\n\n", tokens->content);
    if (tokens->under_tokens) {
        display_tokens(tokens->under_tokens[0], indent + 1);
        display_tokens(tokens->under_tokens[1], indent + 1);
    }
}

Test(Parser, single_command_semicolon)
{
    token_t *token = calloc(1, sizeof(token_t));

    token->content = strdup("ls ; cat -e < Makefile > filetotest; cat filetotest | grep lib");
    token->input_fd = -1;
    token->output_fd = -1;
    remove_outer_parentheses(token->content);
    ll_parser(token);
    printf("==>\n"),
    display_tokens(token, 0);
    printf("<===\n");
}

Test(Parser, single_command_pipe) {
    token_t *token = calloc(1, sizeof(token_t));

    token->content = strdup("((ls -l ; echo hello) | cat -e) > fichier");
    token->input_fd = -1;
    token->output_fd = -1;
    remove_outer_parentheses(token->content);
    ll_parser(token);
    printf("\n"),
    //display_tokens(token, 0);
    printf("\n");

    cr_assert(strcmp(token->under_tokens[0]->content, " (ls -l ; echo Hello) | cat -e  ") == 0);
    cr_assert(strcmp(token->under_tokens[0]->under_tokens[0]->content, "  ls -l ; echo Hello  ") == 0);
    cr_assert(strcmp(token->under_tokens[0]->under_tokens[0]->under_tokens[0]->content, "  ls -l ") == 0);
    cr_assert(strcmp(token->under_tokens[0]->under_tokens[0]->under_tokens[1]->content, " echo Hello  ") == 0);
    cr_assert(strcmp(token->under_tokens[0]->under_tokens[1]->content, " cat -e  ") == 0);
    cr_assert(strcmp(token->under_tokens[1]->content, " grep lib") == 0);
}

Test(Parser, single_command_and)
{
    
}

Test(Parser, multiple_command_pipe) {
    
}

Test(Parser, invalid_null_command_after_pipe) {
    
}
