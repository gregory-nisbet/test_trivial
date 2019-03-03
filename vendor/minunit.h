/* file: minunit.h */
/* source: http://www.jera.com/techinfo/jtns/jtn002.html */
/* added mu_assert_1 and mu_assert_2 */
#ifndef MINUNIT_H_HGUARD
#define MINUNIT_H_HGUARD

#define mu_assert_1(test) \
    mu_assert_2((#test), (test))

#define mu_assert_2(message, test) \
    do {                           \
        if (!(test))               \
            return message;        \
    } while (0)

#define mu_run_test(test)             \
    do {                              \
        const char* message = test(); \
        tests_run++;                  \
        if (message)                  \
            return message;           \
    } while (0)

extern int tests_run;
#endif // MINUNIT_H_HGUARD
