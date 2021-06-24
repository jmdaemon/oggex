# Features
Listed are some possible, and upcoming features for Oggex.

## Work in Progress

#### Minor Tasks
- Setup profiler, and optimize binaries for Clang & GCC
- Find out how to redirect `stderr` into a string to check format output for the unit tests.


- - - - -
## Possible Features

#### Remove dependency on ffmpeg
- Dissect the ffmpeg command, and possibly replace ffmpeg with an included project bin or lib.

#### Support for more audio files
- Do research on possible popular audio file implementations, and be able to embed them using ffmpeg.

#### Encode/Decode with Image Masking
- Implement embedding and extraction with optional image masking.

#### Batch files
- Create functionality for batch file embeding or extracting.
- Make do with a bash script first, and then begin writing functionality once that isn't enough.

#### Add Progress Bar
- A progress bar would be nice for longer embeddings and extractions, however the program executes so quickly anyways that this is not top priority.


- - - - -
## Future Features

#### QT6 GUI
- Create small graphical user interface in QT6.
- Ensure that users have a choice to install either the cli or gui versions respectively.
