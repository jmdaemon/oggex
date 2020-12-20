
Process:
===

1.
- Read an ImageFile with a given path into memory.
- Write the ImageFile to a new file, outputFile.
- Read the outputFile again, and write the ImageFile hash from the ImageFile
- Close ImageFile

2.
- Open the AudioFile that was encoded with ffmpeg
- Read the soundTag into memory, and mask the tag with the hash
- Write the hashed soundTag to the outputFile

3.
- Read the AudioFile into memory, and mask the audio with the hash
- Write the hashed AudioFile to the outPut File
- Close all

Requirements:
===

Must be able to:
- Read entire files into buffers, (4MiB or less)
- - Use new keyword + heap?
- - Read file into stringstream and convert to string?

- Obtain the size of the data(size_t), and the length for the array creation(int)
