#include <iostream>
#include <string>
#include <filesystem>
#include <exception>
#include <fstream>
#include <cassert>
#include <streambuf>
#include <exception>
#include <locale>
#include <regex>

#include <fmt/core.h>
#include <fmt/printf.h>

#include "EmbedAudio.h"
#include "base64.h"

using namespace std;
namespace fs = std::filesystem;

size_t getFileSize(ifstream& file) {
  file.seekg(0, ios::end);
  size_t file_size = file.tellg();
  file.seekg(0, ios::beg);
  return file_size;
}

string dataToString(ifstream& file) {
  ostringstream fileContents;
  fileContents << file.rdbuf();
  string filedata = fileContents.str();
  return filedata;
}

size_t getAudioOffset(ifstream& file, const char* search_term = "OggS") {
  size_t file_size = getFileSize(file);
  fmt::print("\nSize of embedded file: \t\t{} bytes\n", file_size);

  string filedata = dataToString(file);

  size_t found_at = filedata.find(search_term);

  if (file_size == found_at) {
    fmt::fprintf(cerr, "file_size: {} == found_at: {}. Search term not found", file_size, found_at);
    found_at = 0;
  }

  return found_at; 
}

string readFile(fs::path filepath, size_t offset) {
  ifstream file(filepath, ifstream::in | ios::binary);
  size_t file_size = getFileSize(file);
  fmt::print("Audio File size in readFile(): \t{}\t bytes\n", file_size); 
  file.seekg(offset, ios::beg);

  string result = dataToString(file);
  file.close();

  return result;
}

string findSoundTag(fs::path filepath, size_t offset) {
  ifstream file(filepath, ifstream::in | ios::binary);
  string fileContent = dataToString(file);
  file.close();

  size_t index = offset - 100;
  string tag = fileContent.substr(fileContent.find("[", index), fileContent.find("]", index));
  regex exp("(\\[\\w+\\])(\?!OggS)");

  string soundTag = "";
  smatch match;
  if (regex_search(tag, match, exp)) 
    soundTag += match[0]; // tag = [audio02].ogg
  
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
  fmt::print("Audio File offset: \t\t{} \tbytes \n", audioOffset); 

  string audioContent = readFile(filepath, audioOffset);
  string soundTag     = findSoundTag(filepath, audioOffset) + ".ogg"; 
  fmt::print("Sound tag: \t\t\t{}\n\n", soundTag);

  ofstream audioFile(soundTag.c_str(), ifstream::out | ifstream::binary); 
  audioFile.write(audioContent.c_str(), audioContent.length());

  audioFile.close();

   return 0;
}
