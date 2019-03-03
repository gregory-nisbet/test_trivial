#include "minunit.h"
#include "test_trivial.h"
#include <cstdio>

int tests_run = 0;

const char* test_ttr_numtests()
{
    mu_assert_1(ttr_numtests(0) == ttr_bad_zero_tests);
    mu_assert_1(ttr_numtests(-1) == ttr_bad_negative_tests);
    mu_assert_1(ttr_numtests(1) == ttr_good_ok);
    return NULL;
}

const char* all_tests()
{
    mu_run_test(test_ttr_numtests);
    return NULL;
}

int main()
{
    const char* result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    }
    return result != NULL;
}
