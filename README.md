# test\_trivial

A very small unit testing framework for C and C++ based on Perl's Test::More

Here's an example of a test suite using this library:

```
#include "path/to/test_trivial.h"

int main() {
  TTR_NUMTESTS(1);
  TTR_CSTR_EQ_3("a should equal a", "a", "a");
  return TTR_EXIT_STATUS;
}
```

The public interface of this module consists of the macros beginning with TTR\_
