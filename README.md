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

The public interface of this module consists of the macros beginning with `TTR_`.
All function-like macros except for `TTR_NUMTESTS` have their arity as a suffix.
Prior to C99, C did not have a distinct primitive boolean type. The type reported
in the documentation as `bool` is `typedef`d to `int` when compiling the library
as C. `bool` is really `bool` when compiling as C++ so that `operator bool` is selected.
`cstr!` refers to a pointer to a null-terminated string that cannot be a null pointer.
`cstr?` refers to a pointer to a null-terminated string that CAN be a null pointer.

The names and "types" of the macros are described below.

`TTR_NUMTESTS : integer -> void`

begin a new test suite by declaring the number of tests to execute. It is similar to the following Perl fragment.

```
use Test::More tests => 47
```

`TTR_EXIT_STATUS : integer`

`TTR_EXIT_STATUS` expands into the current exit status at the point where the macro is used.

`TTR_OK_1 : bool -> void`

`TTR_OK_1` succeeds if its argument is equal to the boolean true or any integer other than zero
when compiling as C.

`TTR_OK_2 : cstr! * bool -> void`

`TTR_OK_2` is just like `TTR_OK_1` except that it requires an initial argument naming the test.

`TTR_FALSE_1 : bool -> void`

`TTR_FALSE_1` is just like `TTR_OK_1` except that its argument must be false rather than true.

`TTR_FALSE_2 : cstr! * bool -> void`

`TTR_FALSE_2` is just like `TTR_FALSE_1` except that it requires an explicit name as its first argument.

`TTR_CSTR_EQ_3 : cstr! * cstr! * cstr! -> bool`

`TTR_CSTR_EQ_3` takes a name of the test, a left argument, and a right argument. It checks whether the left and right argument
are both not null pointers and that their contents are equal to each other.

`TTR_CSTR_EQ_2 : cstr! * cstr! -> bool`

`TTR_CSTR_EQ_2` is like `TTR_CSTR_EQ_3` but without the explicit name.
