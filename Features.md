# Features
Listed are some possible, and upcoming features for Oggex.


## Work in Progress

#### Human Readable Sizes
- Add feature to Extract/Embed Audio to toggle human readable numbers.
- Sizes will be displayed in either (B, KB, MB, GB);

#### Update Unit Tests
- Update all the unit tests, and look into writing better, more effective tests


- - - - -
## Minor Features

#### Support for Sound Tags Beyond 100 Characters
- Read the entire embedded file from start to finish.
- Improve the regex search in findSoundTag() to find the sound tag more easily.

### TODO
- Setup profiler, and optimize binaries for Clang & GCC
- Make `ninja -C build` and `ninja -C build install` for building local binaries, and for installing binaries to /usr/local


- - - - -
## Possible Features

#### Encode/Decode with Image Masking
- Implement embedding and extraction with optional image masking.

#### Support for more audio files
- Do research on possible popular audio file implementations, and be able to embed them using ffmpeg.

#### Batch files
- Create functionality for batch file embeding or extracting.
- Make do with a bash script first, and then begin writing functionality once that isn't enough.

#### Unicode sound tags
- Try implementing better regex to support Unicode sound tags.


- - - - -
## Future Features

#### QT6 GUI
- Create small graphical user interface in QT6.
- Ensure that users have a choice to install either the cli or gui versions respectively.

#### Add Progress Bar
- A progress bar would be nice for longer embeddings and extractions, however the program executes so quickly anyways that this is not top priority.
