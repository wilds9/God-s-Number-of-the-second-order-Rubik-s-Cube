#!/bin/bash

mkdir -p build/ &&\
    cd build/
gcc -o main.out ../src/main.c
cd .. &&\
    ln -sf build/main.out
