#!/bin/bash

if test 'darwin' '=' "$(uname | tr '[:upper:]' '[:lower:]')"; then
  mac=t
else
  mac=f
fi

set -e
cd "$(dirname "$0")"

make clean
make test-once CC=clang CXX=clang++

make clean
if test "$mac" = t; then
  make test-once "CC=gcc-8"   "CXX=g++-8"
else
  make test-once  CC=gcc       CXX=g++
fi

# TODO: make it possible to run C and C++ tests independently
if test "$mac" = t; then
  :
else
  make clean
  make test-once CC=tcc   CXX=clang++
fi
