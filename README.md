# Oggex
Embed OGG audio files in images and extract audio from images.

1. [Requirements](#Requirements)
2. [Installation](#Installation)
3. [Building](#Building)
2. [Usage](#Usage)
    1. [Embedding Audio](#Embedding%20Audio)
    2. [Extracting Audio](#Extract)


## Requirements 
The following dependencies are required:
- ffmpeg

## Installation
You can download the latest release from the [Releases](https://github.com/jmdaemon/oggex/releases/latest/download/oggex-1.0.tar.gz) page.

# Building
The following dependencies are required for building:
- clang
- cmake
- ninja

``` bash
git clone https://github.com/jmdaemon/oggex.git 
cd oggex
bash build_cmake.sh && bash ninja_make.sh
```

There will be two binaries, `embed` and `extract` which will be found in the ./build/app/ directory.

## Usage

Output files are formatting like this:

`[image.png] +[sound_tag] + [audio.ogg]`

## Embedding Audio

To embed audio files, you need to provide a `[sound_tag]` and an `[audio.ogg]` file.
Note that there is an output file limit of 4MiB (includes the size of the image, audio and length of the sound tag).

#### Example

`$ embed [siamese_cat.png] + [meow01] + [meow01.ogg]`

The output file will be named `[sound_tag].png`. Currently the supported image file formats are:
- jpg/jpeg
- gif
- png
- webm

#### Optional Arguments 
``` bash
$ embed --help
Usage: embed [audio_file] [sound_tag] [image_file]
 Options:
 	-h, --help		Show this help message
 	-f, --fast		Lower image quality
```
The `-f/--fast` argument sets mono audio encoding in ffmpeg.

### Extract
To extract OGG audio files from images, the only requirement is 
that the sound tag is less than 100 characters, and the image file contains a valid OGG audio.

#### Example

`$ extract [meow01.png]`

The binary will extract a `meow01.ogg` file in the same directory as the image file. 
