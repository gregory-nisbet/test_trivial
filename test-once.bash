#! /bin/bash

set -e
set -o pipefail

pr() {
  for fil in "$@"; do
    test -f "$fil"
  done
  env prove "$@"
}

pr_FAIL() {
  for fil in "$@"; do
    test -f "$fil"
  done
  for fil in "$@"; do
    env prove "$fil" && return 10
  done
  return 0
}

echo 'self tests'

obj/test_self.cpp.t

echo 'tests beginning in 0 or 5 should succeed'

# run the test suites that are supposed to succeed
pr obj/001_small_test_suite.cpp.t \
   obj/002_cstr_eq.cpp.t \
   obj/501_small_test_suite.c.t \
   obj/502_cstr_eq.c.t

echo 'tests beginning in 1 or 6 should fail at runtime'

# run the tests that are supposed to fail
echo '(-)'
echo '(-)'
echo '(-)'
pr_FAIL obj/101_FAIL_ok_false.cpp.t             | sed -e 's/^/(-)   /' -e 's/\s+$//'
echo '(-)'
echo '(-)'
echo '(-)'
pr_FAIL obj/102_FAIL_ok_false_anonymous.cpp.t   | sed -e 's/^/(-)   /' -e 's/\s+$//'
echo '(-)'
echo '(-)'
echo '(-)'
pr_FAIL obj/103_FAIL_false_true.cpp.t           | sed -e 's/^/(-)   /' -e 's/\s+$//'
echo '(-)'
echo '(-)'
echo '(-)'
pr_FAIL obj/104_FAIL_false_true_anonymous.cpp.t | sed -e 's/^/(-)   /' -e 's/\s+$//'
echo '(-)'
echo '(-)'
echo '(-)'
