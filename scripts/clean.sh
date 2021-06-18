#!/bin/bash

# clean.sh - Cleans out release and debug directories in build
RELEASE_DIR="build/Release"
DEBUG_DIR="build/Debug"
DEFAULT_DIR="build"

show_usage() {
    echo "Usage: clean.sh [option]"
    echo "      -b, --build         Cleans build directory"
}

if [[ ! -z "$1" ]]; then
    if [[ "$1" == "-b" || "$1" == "--build" ]]; then
        echo "Cleaning build directory"
        #rm -rf $DEFAULT_DIR
    fi
else
    if [[ -d $RELEASE_DIR ]]; then 
        echo "Removing: $RELEASE_DIR"
        rm -rf $RELEASE_DIR
    elif [[ -d $DEBUG_DIR ]]; then
        echo "Removing: $DEBUG_DIR"
        rm -rf $DEBUG_DIR
    else
        echo "No directories to remove."
    fi
fi 

