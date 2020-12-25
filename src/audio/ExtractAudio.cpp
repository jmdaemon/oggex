#include <iostream>
#include <string>
#include <filesystem>
#include <exception>
#include <fstream>
#include <cassert>
#include <streambuf>
#include <exception>

#include <fmt/core.h>
#include <fmt/printf.h>

#include "EmbedAudio.h"

using namespace std;
namespace fs = std::filesystem;

size_t getAudioOffset(ifstream& file, const char* search_term = "OggS") {
  file.seekg(0, ios::end);
  size_t file_size = file.tellg();
  fmt::print("\nSize of embedded file: \t{} bytes\n", file_size);

  file.seekg(0, ios::beg);
  string file_content;
  file_content.reserve(file_size);
  char buffer[16384];
  streamsize chars_read;

  while (file.read(buffer, sizeof buffer), chars_read = file.gcount())
      file_content.append(buffer, chars_read);

  size_t search_term_size = strlen(search_term);

  size_t offset = 0; 
  size_t found_at = 0;
  if (file.eof()) { 
    for (; file_size > offset && (found_at = file_content.find(search_term, offset)) != string::npos; 
        offset = found_at + search_term_size)
      break; 
  }

  if (file_size == found_at) {
    fmt::fprintf(cerr, "file_size: {} == found_at: {}. Search term not found", file_size, found_at);
    found_at = 0;
  }

  return found_at; 
}

string readFile(fs::path filepath, size_t offset) {
  ifstream file(filepath, ifstream::in | ios::binary);
  file.seekg(offset, ios::end);
  size_t file_size = file.tellg();
  fmt::print("Audio File size in readFile(): \t{}\t bytes\n", file_size); 
  file.seekg(offset, ios::beg);

  stringstream content;
  content << file.rdbuf();
  string result = content.str();

  //fmt::print("File content: {}\n", content.str()); 
  return result;
}

string findSoundTag(string file) {
  int start = 0;
  int end = 0;
  string result = "";
  for (int i = 0; i < file.length(); i++) {
    if (file[i] == '[')
      start = i;
    if (file[i] == ']')
      end = i;
  }

  if (start != 0 && end != 0) {
    result = file.substr(start, end);
  }
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

  assert(audioOffset != -1);
  assert(audioOffset != 0);
  fmt::print("Audio File offset: \t\t{} \tbytes \n\n", audioOffset); 

  string audioContent = readFile(filepath, audioOffset);
  //fmt::print("audioContent string: {}\n", audioContent);
  assert(!audioContent.empty());

  //string soundTag = fmt::format("{}.ogg", findSoundTag(audioContent)); 

  string soundTag = (findSoundTag(audioContent) + ".ogg"); 
  assert(!soundTag.empty());
  fmt::print("Sound tag: \t\t{}\n", soundTag);
  //cerr << soundTag << endl;
  ofstream audioFile(soundTag.c_str(), ifstream::out | ifstream::binary); 

  //audioFile.write(audioContent.c_str(), sizeof(char)*audioContent.size());
  audioFile.write(audioContent.c_str(), audioContent.length());
  //audioFile << audioContent;

  file.close();
  audioFile.close();

   // Filter file 
   return 0;

}
