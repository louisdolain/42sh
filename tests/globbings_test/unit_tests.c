#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "globbing.h"
#include "my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(nbr_wdr, test_1, .init = redirect_all_std)
{
    const char *str = "Hello world";
    cr_assert_eq(nbr_wdr(str), 2);
}

Test(nbr_wdr, test_2, .init = redirect_all_std)
{
    const char *str = "HelloWorld";
    cr_assert_eq(nbr_wdr(str), 1);
}

Test(nbr_wdr, test_3, .init = redirect_all_std)
{
    const char *str = "";
    cr_assert_eq(nbr_wdr(str), 0);
}

Test(nbr_wdr, test_4, .init = redirect_all_std)
{
    const char *str = "Hello   World";
    cr_assert_eq(nbr_wdr(str), 2);
}

Test(contains_globbing_pattern, test_5, .init = redirect_all_std)
{
    const char *str = "Hello*";
    cr_assert(contains_globbing_pattern(str));
}

Test(contains_globbing_pattern, test_6, .init = redirect_all_std)
{
    const char *str = "HelloWorld";
    cr_assert_not(contains_globbing_pattern(str));
}

Test(contains_globbing_pattern, test_7, .init = redirect_all_std)
{
    const char *str = "*";
    cr_assert(contains_globbing_pattern(str));
}

Test(contains_globbing_pattern, test_8, .init = redirect_all_std)
{
    const char *str = "*?[";
    cr_assert(contains_globbing_pattern(str));
}

Test(handle_globbing, test_9, .init = redirect_all_std)
{
    char **paths;
    char **parsed_input;
    char **env;
    char cmd[] = "ls *";

    parsed_input = calloc(3, sizeof(char *));
    parsed_input[0] = strdup("ls");
    parsed_input[1] = strdup("*");
    parsed_input[2] = NULL;
    paths = calloc(2, sizeof(char *));
    paths[0] = strdup("/bin");
    paths[1] = NULL;
    env = NULL;
    handle_globbing(cmd, parsed_input, paths, &env);
}

Test(handle_globbing, test_10, .init = redirect_all_std)
{
    char **paths;
    char **parsed_input;
    char **env;
    char cmd[] = "ls -l";

    parsed_input = calloc(3, sizeof(char *));
    parsed_input[0] = strdup("ls");
    parsed_input[1] = strdup("-l");
    parsed_input[2] = NULL;
    paths = calloc(2, sizeof(char *));
    paths[0] = strdup("/bin");
    paths[1] = NULL;
    env = NULL;
    handle_globbing(cmd, parsed_input, paths, &env);
}
