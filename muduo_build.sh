#!/bin/bash

if [ ! -d `pwd`/build ]; then
    mkdir `pwd`/build
fi

cd `pwd`/build &&
    make clean&&
    make

cd ..



