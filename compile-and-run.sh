#!/bin/bash

COMPILER="gcc"

if [[ $# >0 && $1 == "icc" ]] ; then
	COMPILER="icc"
fi

echo -n "Compiler: "
${COMPILER} --version | head -n 1

mkdir -p build/ &&\
    cd build/ &&\
    ${COMPILER} -O3 -o cube.out ../src/main.c &&\
    cd .. &&\
    ln -sf build/cube.out &&\
    time ./cube.out
