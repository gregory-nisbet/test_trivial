#ifndef TEST_TRIVIAL_H_HGUARD
#define TEST_TRIVIAL_H_HGUARD

// TODO: greater consistency left vs right in cstr error names
// TODO: check if diagfmt is NULL
//
// TODO: when comparing cstrings, be able to print where they first differ

#ifdef __cplusplus
#include <cstdio> // -- printf
#include <cstdlib> // -- exit
#include <cstring> // -- strcmp
#else
// specifically do not use stdbool.h
// including stdbool or not is up to the user
#include <stdio.h> // -- printf
#include <stdlib.h> // -- exit
#include <string.h> // strcmp
#endif

#ifdef __cplusplus
#define TEST_TRIVIAL_BOOL bool
#else
#define TEST_TRIVIAL_BOOL int
#endif

static int ttr_current_test = -1; // invalid sentinel value
static int ttr_failed_count = 0; // number of failed tests is initially zero.

enum ttr_error {
    // results beginning with good_
    // mean that the test case itself was successful
    ttr_good_ok = 0,
    ttr_good_NOT_ok = 1, // internal capitalization for legibility
    // results beginning with bad_
    // mean that the user misused the test suite API
    ttr_bad_zero_tests = 1001,
    ttr_bad_negative_tests = 1002,
    ttr_bad_num_tests_unset = 1003,
    ttr_bad_test_name_null = 1004,
    // results beginning with fail_ mean that the
    // test suite failed an internal diagnostic
    ttr_fail_illegal_test_number = 2001,
    // results beginning with pf_ indicate failure of
    // printf or a similar function
    ttr_pf_fail = 3001,
    // a broken precondition isn't really misusing the library
    // it's a different sort of condition
    ttr_precond_null_left_cstr = 4001,
    ttr_precond_null_right_cstr = 4002,
    ttr_precond_null_both_cstrs = 4003
};
typedef enum ttr_error ttr_error;

const char* ttr_pretty_error(ttr_error e)
{
    switch (e) {
    case ttr_good_ok:
        return "good test -- PASS";
    case ttr_good_NOT_ok:
        return "good test -- FAIL";
    case ttr_bad_zero_tests:
        return "library misuse -- told to run zero tests";
    case ttr_bad_negative_tests:
        return "library misuse -- told to run negative tests";
    case ttr_bad_num_tests_unset:
        return "library misuse -- no number of tests given";
    case ttr_bad_test_name_null:
        return "library misuse -- test name cannot be null pointer";
    case ttr_fail_illegal_test_number:
        return "INTERNAL ERROR -- ttr_fail_illegal_test_number";
    case ttr_pf_fail:
        return "RUNTIME ERROR -- ttr_pf_fail";
    case ttr_precond_null_left_cstr:
        return "BROKEN PRECONDITION -- left cstr is a null pointer";
    case ttr_precond_null_right_cstr:
        return "BROKEN PRECONDITION -- right cstr is a null pointer";
    case ttr_precond_null_both_cstrs:
        return "BROKEN PRECONDITION -- both cstrs are null pointers";
    }
    // unreachable
    abort();
    return "";
}

ttr_error ttr_numtests(int n)
{
    if (n == 0) {
        return ttr_bad_zero_tests;
    }
    if (n < 0) {
        return ttr_bad_negative_tests;
    }
    printf("%d..%d\n", 1, n);
    ttr_current_test = 1;
    return ttr_good_ok;
}

// specifically prevent functions that return int or something that converts to
// char from picking up a defined function

ttr_error ttr_ok_impl(const char* name, TEST_TRIVIAL_BOOL val, const char* diagfmt, int line)
{
    if (ttr_current_test == -1) {
        return ttr_bad_num_tests_unset;
    } else if (ttr_current_test <= 0) {
        return ttr_fail_illegal_test_number;
    } else if (!name) {
        return ttr_bad_test_name_null;
    }
    int old_test = ttr_current_test;
    ttr_current_test += 1;
    if (val) {
        printf("ok %d     - %s\n", old_test, name);
        return ttr_good_ok;
    } else {
        printf("not ok %d - %s\n", old_test, name);
        printf(diagfmt, line);
        return ttr_good_NOT_ok;
    }
}

// compare two c strings for equality
ttr_error ttr_cstr_eq_impl(const char* name, const char* left, const char* right, const char* diagfmt, int line)
{
    if (ttr_current_test == -1) {
        return ttr_bad_num_tests_unset;
    } else if (ttr_current_test <= 0) {
        return ttr_fail_illegal_test_number;
    } else if (!name) {
        return ttr_bad_test_name_null;
    } else if (!left && !right) {
        return ttr_precond_null_both_cstrs;
    } else if (!left) {
        return ttr_precond_null_left_cstr;
    } else if (!right) {
        return ttr_precond_null_right_cstr;
    }
    int old_test = ttr_current_test;
    ttr_current_test += 1;
    if (0 == strcmp(left, right)) {
        printf("ok %d     - %s\n", old_test, name);
        return ttr_good_ok;
    } else {
        printf("not ok %d - %s\n", old_test, name);
        printf(diagfmt, line);
        return ttr_good_NOT_ok;
    }
}

void ttr_handle_error(ttr_error e)
{
    switch (e) {
    case ttr_good_ok:
        break;
    case ttr_good_NOT_ok:
        ttr_failed_count += 1;
        break;
    // leftover cases
    case ttr_bad_zero_tests:
    case ttr_bad_negative_tests:
    case ttr_bad_num_tests_unset:
    case ttr_fail_illegal_test_number:
    case ttr_pf_fail:
    case ttr_precond_null_left_cstr:
    case ttr_precond_null_right_cstr:
    case ttr_precond_null_both_cstrs:
    case ttr_bad_test_name_null:
        fprintf(stderr, "FATAL ERROR %d (%s)\n", e, ttr_pretty_error(e));
        exit(2);
        break;
    }
}

void ttr_ok_handled(const char* n, TEST_TRIVIAL_BOOL val, const char* diagfmt, int line)
{
    ttr_error e = ttr_ok_impl(n, val, diagfmt, line);
    ttr_handle_error(e);
}

void ttr_cstr_eq_handled(const char* name, const char* left, const char* right, const char* diagfmt, int line)
{
    ttr_error e = ttr_cstr_eq_impl(name, left, right, diagfmt, line);
    ttr_handle_error(e);
}

#define TTR_NUMTESTS(n) (ttr_handle_error(ttr_numtests(n)))

#define TTR_OK_2(n, val)                             \
    (ttr_ok_handled((n), (val),                      \
        ("#   (+) expected " #val " to be true\n"    \
         "#   from file " __FILE__ " on line %d\n"), \
        __LINE__))

#define TTR_OK_1(val) (TTR_OK_2((#val), (val)))

#define TTR_FALSE_2(n, val)                          \
    (ttr_ok_handled((n), (!(val)),                   \
        ("#   (-) expected #val to be FALSE\n"       \
         "#   from file " __FILE__ " on line %d\n"), \
        __LINE__))

#define TTR_FALSE_1(val) (TTR_FALSE_2((#val), (val)))

#define TTR_CSTR_EQ_3(n, left, right)                \
    (ttr_cstr_eq_handled((n), (left), (right),       \
        ("#   (+) expected C-string "                \
         "(" #left ")"                               \
         " to equal "                                \
         "(" #right ")"                              \
         "\n"                                        \
         "#   from file " __FILE__ " on line %d\n"), \
        __LINE__))

#define TTR_CSTR_EQ_2(left, right)                \
    TTR_CSTR_EQ_3("strcmp(" #left ", " #right ")" \
                  " == "                          \
                  "0",                            \
        left, right)

#define TTR_EXIT_STATUS ((ttr_failed_count <= 0) ? 0 : 1)

#endif // TEST_TRIVIAL_H_HGUARD
