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

size_t getAudioOffset(ifstream& file, const char* search_term = "OggS") {
  file.seekg(0, ios::end);
  size_t file_size = file.tellg();
  fmt::print("\nSize of embedded file: \t\t{} bytes\n", file_size);

  file.seekg(0, ios::beg);

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
  file.seekg(offset, ios::end);
  size_t file_size = file.tellg();
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

  file.seekg(0, ios::end);
  size_t file_size = file.tellg();

  file.seekg(0, ios::beg);

  stringstream content;
  content << file.rdbuf();
  file.close();
  string fileContent = content.str();

  size_t fileContentSize = offset;
  size_t index = fileContentSize - 10;

  int start = fileContent.find("[", index);
  int end   = fileContent.find("]", index);

  string tag = fileContent.substr(start, end);
  regex exp("(\\[\\w+\\])(\?!OggS)");

  string result = "";

  smatch match;
  if (regex_search(tag, match, exp))
      result += match[0];
  
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
  //file.close();

  //assert(audioOffset != -1);
  //assert(audioOffset != 0);
  fmt::print("Audio File offset: \t\t{} \tbytes \n\n", audioOffset); 


  file.seekg(audioOffset, ios::beg);

  fs::path tempfilepath = "temp.ogg";
  ofstream tempFile(tempfilepath, ifstream::out | ifstream::binary);
  tempFile << file.rdbuf();
  file.close();

  tempFile.close();

  string audioContent = readFile(filepath, audioOffset);
  assert(!audioContent.empty());
  
  string soundTag = (findSoundTag(filepath, audioOffset) + ".ogg"); 
  assert(!soundTag.empty());
  //fmt::print("Sound tag: \t\t{}\n", soundTag);
  //cerr << soundTag << endl;
  //ofstream audioFile("audio01.ogg", ifstream::out | ifstream::binary); 
  ofstream audioFile(soundTag.c_str(), ifstream::out | ifstream::binary); 

  //audioFile.write(audioContent.c_str(), sizeof(char)*audioContent.size());
  audioFile.write(audioContent.c_str(), audioContent.length());
  //audioFile << audioContent;

  //file.close();
  audioFile.close();

   return 0;
}
