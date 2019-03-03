#include "../../include/test_trivial.h"

int main()
{
    TTR_NUMTESTS(1);
    TTR_OK_2("false is not TRUE should fail", false);
    return TTR_EXIT_STATUS;
}
