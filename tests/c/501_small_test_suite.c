#include "../../include/test_trivial.h"

int main()
{
    TTR_NUMTESTS(4);
    TTR_OK_2("named ok test", 1);
    TTR_OK_1(1);
    TTR_FALSE_2("named false test", 0);
    TTR_FALSE_1(0);
    return TTR_EXIT_STATUS;
}
