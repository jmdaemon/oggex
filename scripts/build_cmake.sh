#!/bin/bash

GCC="$(which g++)"
CLANG="$(which clang)"

CMAKE_VERSION="$(cmake --version | grep version | cut -d ' ' -f 3)"
CMAKE_REQUIRED="3.1.9"

function cmake-build-cached() {
    cd build
    cmake -G Ninja ../
}

function cmake-build() {
     if [ -z $CLANG ]; then 
         build-clang
     elif [ -z $GCC ]; then
         build-gcc
     else 
         echo "No compiler"
     fi
}

function build-clang() {
    CC=clang CXX=clang++ cmake -S . -B build -G Ninja
}

function build-gcc() {
    CC=gcc CXX=g++ cmake -S . -B build -G Ninja
} 

#if [ "$(printf '%s\n' "$CMAKE_REQUIRED" "$CMAKE_VERSION" | sort -V | head -n1)" = "$CMAKE_REQUIRED" ]; then 
    #cmake-build-cached
#else 
    cmake-build
#fi
