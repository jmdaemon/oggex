#!/bin/bash

THREADS=$(cat /proc/cpuinfo | grep processor | awk '{print $3}' | awk 'min == "" || $1<min{min=$1} $1>max{max=$1} END{print max}')

cd build 
ninja -j${THREADS}
