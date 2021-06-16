#include <cstdio>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include <fmt/core.h>
#include <fmt/printf.h>

#include "EmbedAudio.h"

using namespace std;
namespace fs = std::filesystem;

size_t getAudioOffset(ifstream& file, const char* search_term = "OggS") {
  size_t file_size = sizeOf(file);
  fmt::print("Size of embedded file: \t\t{} bytes\n", file_size);

  string filedata = dataToString(file);

  size_t found_at = filedata.find(search_term);

  if (file_size == found_at) {
    fmt::print(stderr, "file_size: {} == found_at: {}. Search term not found", file_size, found_at);
    found_at = 0;
  }

  return found_at; 
}

string readFile(fs::path filepath, size_t offset) {
  ifstream file(filepath, ifstream::in | ifstream::binary);
  size_t file_size = sizeOf(file);
  fmt::print("Audio File Size in readFile(): \t{} bytes\n", file_size); 
  file.seekg(offset, ios::beg);

  string result = dataToString(file);
  file.close();

  return result;
}

string findSoundTag(fs::path filepath, size_t offset) {
  ifstream file(filepath, ifstream::in | ifstream::binary);
  string fileContent = dataToString(file);
  file.close();

  size_t start    = fileContent.find("[", offset - 101);
  size_t end      = fileContent.find("]", offset - 1);
  fmt::print("SoundTag Start: \t\t\t{} \tbytes\n", start);
  fmt::print("SoundTag End: \t\t\t{} \tbytes\n", end);

  string tag = fileContent.substr(start, end);
  //regex exp("(\\[\\w+\\])(\?!OggS)");
  regex exp("(\\[\\w+\\])");

  string soundTag = "";
  smatch match;
  if (regex_search(tag, match, exp)) 
    soundTag = match[0]; // tag = [audio02].ogg
  
  string result = soundTag.substr(1,  soundTag.length() - 2); // tag = audio02.ogg
  return result; 
}

int extract(fs::path filepath) {

  // Find section where ogg file begins.
  // Find audio tag, store in string
  // Slice image file into two
  // - Read the audio file path after the image file start, until file end
  // Write to new audio file with audio tag

  ifstream file(filepath, ifstream::in | ifstream::binary);
  if (isCorrupted(filepath, file)) { throw exception(); }

  size_t audioOffset = getAudioOffset(file);
  fmt::print("Audio File Offset: \t\t\t{} \tbytes\n", audioOffset); 
  file.close();

  string audioContent = readFile(filepath, audioOffset);
  string soundTag     = findSoundTag(filepath, audioOffset) + ".ogg"; 
  fmt::print("Sound tag: \t\t\t\t\"{}\"\n\n", soundTag);

  ofstream audioFile(soundTag.c_str(), ifstream::out | ifstream::binary); 
  audioFile.write(audioContent.c_str(), audioContent.length());

  audioFile.close();

   return 0;
}
