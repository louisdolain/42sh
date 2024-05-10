#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "globbing.h"

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
