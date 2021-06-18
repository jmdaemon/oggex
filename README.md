# Oggex
Embed and extract OGG audio files in images using sound tags.

1. [Requirements](#Requirements)
2. [Installation](#Installation)
3. [Building from Source](#Building)
2. [Usage](#Usage)
    1. [Embedding](#Embedding)
    2. [Extracting](#Extracting)


## Requirements 
The following dependencies are required:
- ffmpeg

## Installation

### Release
You can download it [here](https://github.com/jmdaemon/oggex/releases/latest/download/oggex-1.0.tar.gz) or get the latest release from the [Releases](https://github.com/jmdaemon/oggex/releases/) page.

### Building
The following build dependencies are required:
- clang or gcc
- cmake (3.1.9)
- ninja

``` bash
git clone https://github.com/jmdaemon/oggex.git
cd oggex
./scripts/build.sh
cd build
sudo ninja install
```
The binary will be found under `/usr/local/bin`.
To uninstall, write `sudo ninja uninstall ` in the same build directory.
The `oggex` binary can also be found under `build/app`.
Additional parameters can be specified to `build.sh` for greater flexibility.

## Usage

```
Usage: oggex [embed/extract] -a [audio] -t [soundtag] -i [image]
Options:

          -h,  	--help		Show this help message
          -v,  	--verbose	Display program output and debugging information
          -a,  			The file path to the audio file
          -i,  			The file path to the image file
          -t,  			The caption or tag for the audio file

    Embedding:
          embed, 	-m             Embed an audio file
          -f,  	--fast         Enable Mono Audio Channel encoding
          -ig, 	--ignore-limit Allows you to encode files greater than 4 MiB
          -d,  	--dest         Change the output file name.

    Encoding:
          extract, -x                Extract audio from an image
          -ad,                       Change the audio file output file name.
          -id,                       Change the image file output file name.

```

### Embedding
```
$ oggex embed -a audio.ogg -i image.png -t "soundtag"
```

**Note:** The maximum output file size, includes the size of the image, audio, and the length of the sound tag.

Currently the supported image file formats are:
- jpg/jpeg
- gif
- png
- webm

The output file will be named `[image]-embed.png`

### Extracting

```
$ oggex extract -i inputFile-embed.png
```

The extracted output file will be called `[soundtag].ogg` and there will also be the original `[image]` file to re-embed if needed.
