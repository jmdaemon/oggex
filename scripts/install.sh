#!/bin/bash

show_usage() {
    echo "Usage: install.sh [SOURCE] [DEST]"
    echo ""
}
if [[ -z $1 || -z $2 ]]; then 
    show_usage
elif [[ ! -z $1 || ! -z $2 ]]; then 
    cmake --install "${1}" --prefix "${2}"
else
    # Make sure you are in the project build directory
    cmake --install . --prefix "usr/install"
fi
