# Oggex

Embed and extract OGG audio files in images using sound tags.

1. [Usage](#usage)
    1. [Embedding Sounds](#embedding-sounds)
    2. [Extracting Sounds](#extracting-sounds)
2. [Building](#building)
    1. [Ninja](ninja)
    2. [Unix Makefiles](unix-makefiles)
3. [Install](#install)

## Usage


### Embedding Sounds

To embed a sound into an image file, run:
``` bash
oggex embed -a audio.ogg -i image.png -t "soundtag"
```

where `audio.ogg` is the file path to your sound, `image.png` is the image to embed the sound in,
and `soundtag` is the sound tag used to identify your sound.

Note: Be wary of creating embedded images that are 4MiB or greater as this hasn't been tested yet.

Note: Sound tags have no character limit except maybe for the file size limit above.
Unicode sound tags are also supported.

Currently the supported image file formats are:

- jpg/jpeg
- gif
- png
- webm

The output file name for the embedd image will be named: `[image]-embed.png`.

### Extracting Sounds

To extract sounds from embedded images run:

``` bash
oggex extract -i inputFile-embed.png
```

This will output the original image file, alongside the
sound file with the name of the `soundtag` as its file name.

## Building

This project supports the following build configurations:

For building with GCC:

- gcc-debug-ninja
- gcc-release-ninja
- gcc-debug-unix-makefiles
- gcc-release-unix-makefiles

For building with Clang:

- clang-debug-ninja
- clang-release-ninja
- clang-debug-unix-makefiles
- clang-release-unix-makefiles

You can specify which preset to build using the `--preset` CMake flag.

The build output will generate libraries in the `src` directories,
and the cli oggex binary can be found in `build/app`.

### Ninja

To build this project using the Ninja generator, run:

``` bash
cmake --preset=gcc-release-ninja

```

This will generate the Ninja build files in `build/gcc-release-ninja`

Then you can build the project with:

``` bash
cd build/gcc-release-ninja && ninja
```

### Unix Makefiles

To build this project using the Unix Makefiles generator, run:

``` bash
cmake --preset=gcc-release-unix-makefiles
```

Then to build the project:
``` bash
cd build/gcc-release-ninja && make
```

## Install

To install oggex with Ninja, run:
``` bash
sudo ninja install
```

To install oggex with make, run:
``` bash
sudo make install
```
