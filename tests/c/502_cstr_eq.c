#include "../../include/test_trivial.h"

int main()
{
    TTR_NUMTESTS(2);
    TTR_CSTR_EQ_3("named ok test", "a", "a");
    TTR_CSTR_EQ_2("a", "a");
    return TTR_EXIT_STATUS;
}
