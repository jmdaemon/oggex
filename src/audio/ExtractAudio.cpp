#include "ExtractAudio.h"

using namespace std;
namespace fs = std::filesystem;

size_t getAudioOffset(Data& data, const char* search_term) { 
  ifstream file(data.image.getImage(), ifstream::in | ifstream::binary);
  size_t file_size = sizeOf(file);
  if (data.showDebugInfo) { fmt::print("Size of Embedded File \t\t: {} \tbytes\n", file_size); }
  size_t audioOffset = dataToString(file).find(search_term);

  if (file_size == audioOffset) {
    fmt::print(stderr, "Audio offset not found");
    audioOffset = 0;
  }
  file.close();
  return audioOffset; 
}

string readFile(Data& data, size_t offset) {
  ifstream file(data.image.getImage(), ifstream::in | ifstream::binary);
  if (data.showDebugInfo) { fmt::print("Audio File Size \t\t: {} \tbytes\n", sizeOf(file) - offset); }

  file.seekg(offset, ios::beg);
  string result = dataToString(file);
  file.close();
  return result;
}

string findSoundTag(Data& data, size_t offset) {
  ifstream file(data.image.getImage(), ifstream::in | ifstream::binary);
  string fileData = dataToString(file);
  file.close();

  string tag = fileData.substr(offset - 100, offset);
  //regex exp("(\\[\\w+\\])(\?!OggS)");
  regex exp("(\\[\\w+\\])");

  if (data.showDebugInfo) { fmt::print("\n================ Sound Tag ================\n"); }
  string soundTag = "";
  smatch match;
  if (regex_search(tag, match, exp)) { 
    soundTag = match[0]; // tag = [audio02].ogg
    if (data.showDebugInfo) {
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
  size_t audioOffset = getAudioOffset(data);
  if (data.showDebugInfo) {
    fmt::print("\n================ File Sizes ================\n");
    fmt::print("Audio File Offset \t\t: {} \tbytes\n", audioOffset); 
  }

  string audioContent       = readFile(data, audioOffset);
  string soundTag           = findSoundTag(data, audioOffset); 
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
