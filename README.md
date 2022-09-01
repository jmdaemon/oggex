# Oggex

Embed and extract OGG audio files in images using sound tags.

## Rationale

This project was developed as a steganographic and archiving tool.

## Table of Contents

- [Rationale](#rationale)
- [Usage](#usage)
- [Build](#build)
- [Install](#install)

## Usage

``` bash
# Embed sounds in images
oggex embed -a audio.ogg -i image.png -t "audio01"

# Extract sounds and images
oggex extract -i "embedded.png"
```

For more information and options, run `oggex -h`.

## Build

This project supports the following CMake presets:

- gcc-debug-ninja
- gcc-release-ninja
- gcc-debug-unix-makefiles
- gcc-release-unix-makefiles

- clang-debug-ninja
- clang-release-ninja
- clang-debug-unix-makefiles
- clang-release-unix-makefiles


To build with Ninja:

``` bash
cmake --preset=gcc-release-ninja
cd build/gcc-release-ninja
ninja
```

To build with Make:

``` bash
cmake --preset=gcc-release-unix-makefiles
cd build/gcc-release-unix-makefiles
make
```

To build with Meson:
``` bash
meson build/meson/release --buildtype release
cd build/meson/release
meson compile
```

## Install
There are three different exceutables that you can choose to install from: `oggex`, `oggex-qt`, `oggex-gtk`.

`oggex`: Pure cli executable.
`oggex-qt`: GUI version made with QT6.
`oggex-gtk`: GUI version made with GTK4.

To install:

``` bash
sudo ninja install
# or
sudo make install
# or
meson install
```

## Contribute

Contributions and suggestions are welcome. Feel free to suggest ideas or potential features.
If you need to contact me you can do so by my [email](josephm.diza@gmail.com)

## Features

Potential features

- Manpages for viewing options and flags.
- Online documentation
- Direct encoding/linking with ffmpeg.
- Flag to toggle optional file masking.
- Progress Bar during encoding
