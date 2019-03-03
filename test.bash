#!/bin/bash

set -e
cd "$(dirname "$0")"

make clean
make test-once CC=clang CXX=clang++

make clean
make test-once CC=gcc   CXX=g++

# TODO: make it possible to run C and C++ tests independently
make clean
make test-once CC=tcc   CXX=clang++
