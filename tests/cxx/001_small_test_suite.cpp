#include "../../include/test_trivial.h"

int main()
{
    TTR_NUMTESTS(4);
    TTR_OK_2("named ok test", true);
    TTR_OK_1(true);
    TTR_FALSE_2("named false test", false);
    TTR_FALSE_1(false);
    return TTR_EXIT_STATUS;
}
