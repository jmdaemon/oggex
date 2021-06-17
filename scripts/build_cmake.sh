#!/bin/bash

function cmakeBuildOld() {
    cd build
    cmake -G Ninja ../
}

function cmakeBuild() {
    CC=clang CXX=clang++ cmake -S . -B build -G Ninja
}

cmakever="$( cmake --version | grep version | cut -d ' ' -f 3 )"
required="3.0.0"
 if [ "$(printf '%s\n' "$requiredver" "$currentver" | sort -V | head -n1)" = "$requiredver" ]; then 
     cmakeBuild
 else
     cmakeBuildOld
 fi
