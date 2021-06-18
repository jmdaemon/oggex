#!/bin/bash

# build.sh - Builds Release or Debug configurations for Oggex
# Execute this script from the project root directory

# TODO: Generate project with dirs set to project version
DEFAULT_DIR="build"
RELEASE_DIR="build/Release"
DEBUG_DIR="build/Debug"

build_release() {
    mkdir $RELEASE_DIR 
    CC="${1}" CXX="${2}" cmake -S . -B $RELEASE_DIR -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF
    cd $RELEASE_DIR
    ninja 
}

build_debug() {
    mkdir $DEBUG_DIR
    CC="${1}" CXX="${2}" cmake -S . -B $DEBUG_DIR -G Ninja -DCMAKE_BUILD_TYPE=Debug
    cd $DEBUG_DIR
    ninja 
}

build_default() {
     CC=$1 CXX=$2 cmake -S . -B $DEFAULT_DIR -G Ninja
}

show_usage() {
    echo "Usage: ./scripts/build.sh [options]"
    echo ""
    echo "    Configure"
    echo "      ./scripts/build.sh  Build in Default configuration"
    echo "      -r, --release       Build in Release configuration"
    echo "      -d, --debug         Build in Debug configuration"
    echo "      -c, --clang         Compile with Clang"
    echo "      -g, --gcc           Compile with GCC"
    echo ""
    echo "    Build "
    echo "      -m, --make          Make Oggex with Ninja"
    echo ""
    echo "    Install "
    echo "      -i, --install       Creates the Oggex binary in build/install/bin "
    echo "                                                  or  build/Debug/install/bin"
    echo "                                                  or  build/Release/install/bin"
    echo "    Test"
    echo "      -t, --test          Run tests in Ninja"
    echo "      -v, --verbose       Show debugging information"
    echo ""
}

CMAKE_VERSION="$(cmake --version | grep version | cut -d ' ' -f 3)"
CMAKE_REQUIRED="3.0.0"

if [ ! "$(printf '%s\n' "$CMAKE_REQUIRED" "$CMAKE_VERSION" | sort -V | head -n1)" = "$CMAKE_REQUIRED" ]; then 
    echo "Your cmake version must be greater than or equal to 3.0.0"
    exit 1;
fi

CC=""
CXX=""

while true; do
case $1 in 
    "-h" | --help) 
        show_usage 
        break # Replace with die
        ;; 
    "-g" | --gcc) 
        CC="gcc"
        CXX="g++"
        shift 
        ;;
    "-c" | --clang)
        CC="clang"
        CXX="clang++"
        shift 
        ;;
    * | "") 
        CLANG="$(which clang++)" 
        GCC="$(which g++)"
        if [[ ( ! -z "$CLANG") ]]; then 
            CC="clang"
            CXX="clang++"
        elif [[ ( ! -z "$GCC") ]]; then 
            CC="gcc"
            CXX="g++"
        else 
            echo "No compatible compiler installed." 
        fi
        ;;
esac
BUILT_DIR=${DEFAULT_DIR}
case $1 in 
    "-r" | --release) 
        build_release ${CC} ${CXX} 
        BUILT_DIR=${RELEASE_DIR}
        shift
        break
        ;; 
    "-d" | --debug) 
        build_debug ${CC} ${CXX}
        BUILT_DIR=${DEBUG_DIR}
        shift
        break
        ;; 
    "") 
        build_default CC CXX
        BUILT_DIR=${DEFAULT_DIR}
        shift
        break
        ;;
esac 
  case $1 in 
      "-m" | --make) 
          THREADS=$(cat /proc/cpuinfo | grep processor | awk '{print $3}' | awk 'min == "" || $1<min{min=$1} $1>max{max=$1} END{print max}')
          cd ${BUILT_DIR} 
          ninja -j${THREADS}
          break
          ;; 
      "-t" | --test)
          cd ${BUILT_DIR}
          shift
          case $1 in
              -v)
                  ctest -V
                  ;;
              "")
                  ctest
                  ;;
          esac
          break
          ;;
  esac
  case $1 in
      "-i" | --install)
          cd ${BUILT_DIR}
          cmake --install .
          break
          ;;
      *) 
          show_usage
          break
          ;;
  esac
done 
