#include "ExtractAudio.h"

using namespace std;
namespace fs = std::filesystem;

size_t getOffset(std::filesystem::path filepath, const char* searchTerm) { 
  ifstream file(filepath, ifstream::in | ifstream::binary);
  size_t offset = dataToString(file).find(searchTerm);
  if (sizeOf(filepath) == offset) {
    fmt::print(stderr, "Audio offset not found");
    offset = 0;
  }
  file.close();
  return offset; 
}

string readFile(Data& data, size_t offset) {
  ifstream file(data.image.getImage(), ifstream::in | ifstream::binary);
  file.seekg(offset, ios::beg);
  string result = dataToString(file);
  file.close();
  return result;
}

string findSoundTag(Data& data, string fileData, size_t offset) {
  string tag = fileData.substr(offset - 100, offset);
  //regex exp("(\\[\\w+\\])(\?!OggS)");
  regex exp("(\\[\\w+\\])");

  string soundTag = "";
  smatch match;
  if (regex_search(tag, match, exp)) { 
    soundTag = match[0]; // tag = [audio02].ogg
    if (data.showDebugInfo) { 
      fmt::print("\n================ Sound Tag ================\n");
      fmt::print("Tag: \t\t\t\t: {}\n", soundTag);
    }
  }
  string result = "";
  if (!soundTag.empty()) {
    result = soundTag.substr(1,  soundTag.length() - 2); // tag = audio02.ogg
    if (data.showDebugInfo) {
      fmt::print("Stripped Tag: \t\t\t: {}\n", result);
    }
  } else {
    fmt::print(stderr, "Sound Tag was not found.\n");
  }
  return result; 
}

int extract(Data data) {
  size_t embeddedFileSize   = sizeOf(data.image.getImage());
  size_t audioOffset        = getOffset(data.image.getImage());
  size_t audioFileSize      = sizeOf(data.image.getImage(), audioOffset);
  if (data.showDebugInfo) {
    fmt::print("\n================ File Sizes ================\n"); 
    fmt::print("Size of Embedded File \t\t: {} \tbytes\n" , embeddedFileSize);
    fmt::print("Audio File Size \t\t: {} \tbytes\n\n"     , audioFileSize);
    fmt::print("\n================ File Offsets ================\n"); 
    fmt::print("Audio File Offset \t\t: {} \tbytes\n"     , audioOffset); 
  }

  string embeddedFileData   = readFile(data, 0);
  string audioContent       = readFile(data, audioOffset);
  string soundTag           = findSoundTag(data, embeddedFileData, audioOffset); 
  if (soundTag.empty()) { 
    return -1; 
  } else { 
    soundTag += ".ogg";
  }
  if (data.showDebugInfo) { fmt::print("Output Audio File \t\t: {}\n\n", soundTag); }
  fmt::print("Extracting audio file as \"{}\"\n", soundTag);

  ofstream audioFile(soundTag.c_str(), ifstream::out | ifstream::binary); 
  audioFile.write(audioContent.c_str(), audioContent.length());
  audioFile.close();

   return 0;
}
