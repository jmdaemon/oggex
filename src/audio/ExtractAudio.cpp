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

size_t getAudioOffset(ifstream& file, const char* search_term = "OggS") {
  size_t file_size = getFileSize(file);
  fmt::print("\nSize of embedded file: \t\t{} bytes\n", file_size);

  ostringstream fileContents;
  fileContents << file.rdbuf();
  string filedata = fileContents.str();

  size_t found_at = 0;
  found_at = filedata.find(search_term);

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

  stringstream content;
  content << file.rdbuf();
  file.close();
  string result = content.str();

  return result;
}

string findSoundTag(fs::path filepath, size_t offset) {
  ifstream file(filepath, ifstream::in | ios::binary);
  size_t file_size = getFileSize(file);

  stringstream content;
  content << file.rdbuf();
  file.close();
  string fileContent = content.str();

  size_t fileContentSize = offset;
  size_t index = fileContentSize - 100;

  int start = fileContent.find("[", index);
  int end   = fileContent.find("]", index);

  string tag = fileContent.substr(start, end);
  regex exp("(\\[\\w+\\])(\?!OggS)");

  string soundTag = "";

  smatch match;
  if (regex_search(tag, match, exp)) 
    soundTag += match[0]; // tag = [audio02].ogg
  
  start = 1;
  end = soundTag.length() - 2;
  
  string result = soundTag.substr(start, end); // tag = audio02.ogg
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
  fmt::print("Audio File offset: \t\t{} \tbytes \n\n", audioOffset); 

  file.seekg(audioOffset, ios::beg);

  string audioContent = readFile(filepath, audioOffset);

  string soundTag = (findSoundTag(filepath, audioOffset) + ".ogg"); 
  fmt::print("Sound tag: \t\t{}\n", soundTag);

  ofstream audioFile(soundTag.c_str(), ifstream::out | ifstream::binary); 
  audioFile.write(audioContent.c_str(), audioContent.length());

  audioFile.close();

   return 0;
}
