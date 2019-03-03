#! /bin/bash

set -e
set -o pipefail

pr() {
  for fil in "$@"; do
    test -f "$fil"
  done
  env prove "$@"
}

pr_FAIL_one() {
  for fil in "$@"; do
    test -f "$fil"
  done
  for fil in "$@"; do
    env prove "$fil" && return 10
  done
  return 0
}

echo 'tests beginning in 0 or 5 should succeed'

# run the test suites that are supposed to succeed
pr obj/001_small_test_suite.cpp.t \
   obj/002_cstr_eq.cpp.t \
   obj/501_small_test_suite.c.t \
   obj/502_cstr_eq.c.t

echo 'tests beginning in 1 or 6 should fail'

# run the tests that are supposed to fail
pr_FAIL_one obj/101_FAIL_ok_should_be_true.cpp.t | sed 's/^/(-) /'
