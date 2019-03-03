#include "../../include/test_trivial.h"

int main()
{
    TTR_NUMTESTS(1);
    TTR_FALSE_2("true is not FALSE should fail", true);
    return TTR_EXIT_STATUS;
}
