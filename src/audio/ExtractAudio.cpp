#include <iostream>
#include <string>
#include <filesystem>
#include <exception>
#include <fstream>
#include <regex>
#include <cstdio>

#include <fmt/core.h>
#include <fmt/printf.h>

#include "EmbedAudio.h"

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
//size_t getAudioOffset(ifstream& file, const char* search_term = "\x4f\x67\x67\x53\x00\x02") {
//size_t getAudioOffset(ifstream& file, const char* search_term) {
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
  //ifstream file(filepath, ifstream::in | ios::binary);
  ifstream file(filepath, ifstream::in | ifstream::binary);
  size_t file_size = getFileSize(file);
  fmt::print("Audio File size in readFile(): \t{} bytes\n", file_size); 
  file.seekg(offset, ios::beg);

  string result = dataToString(file);
  file.close();

  return result;
}

string findSoundTag(fs::path filepath, size_t offset) {
//string findSoundTag(string audioContent, size_t offset) {
  ifstream file(filepath, ifstream::in | ifstream::binary);
  size_t fileSize = getFileSize(file);
  string fileContent = dataToString(file);
  file.close();

  //size_t index = offset - 4;
  //size_t index = offset - 100;
  //string tag = fileContent.substr(fileContent.find("[", index), fileContent.find("]", index));
  //string tag = fileContent.substr(fileContent.find('[', index), fileContent.find(']', index));
  //int end     = fileContent.find("]OggS", index);
  //int end     = fileContent.find("]OggS", index);
  //int start   = fileContent.find("[", end - 100);
  //int start   = fileContent.find("[", index - 100);
  //int start   = fileContent.find("[", end - 104);
  //string tag = fileContent.substr(fileContent.find("[", index), fileContent.find("]OggS", index));
  //string tag = fileContent.substr(start, index);
  //string tag = fileContent.substr(start, end);
  //int start   = fileContent.find("[", index);
  //size_t end     = fileContent.find("]OggS", offset); 
  //size_t start   = fileContent.find("[", offset - 100);
  //size_t end     = fileContent.find("\x5d\x4f\x67\x67\x00\x02", offset); 
  //size_t end      = fileContent.find("]OggS", offset - 10, 1);
  //size_t start    = fileContent.find("[", offset - 20, 1);
  //size_t end      = fileContent.find("]OggS", offset - 1);
  //size_t end      = 19277;
  //size_t start    = 19269;
  //size_t end      = offset;
  //size_t start    = offset - 100;
  fmt::print("Filesize: \t{}\n", fileSize);
  //size_t endIndex = fileSize - 10;
  //size_t startIndex = fileSize - 110;
  //size_t end      = fileContent.find("]OggS", endIndex);
  //size_t start    = fileContent.find("[", startIndex);
  size_t start    = fileContent.find("[", offset - 101);
  size_t end      = fileContent.find("]", offset - 1);
  fmt::print("Start: \t{}\nEnd: \t{}\n", start, end);

  //size_t          = offset - 
  //size_t start    = fileContent.find("[", offset - 100);
  //size_t start;
  ////size_t start   = fileContent.find("\x5d", offset - 40);
  //for (size_t i = 0; i > 0 && i <= 100; i++) {
    ////if (fileContent.find("\x5d", offset - i)) {
    //if (fileContent.at(offset - i) == '[') {
      //start = offset - i;
      //break;
    //}
  //}

  //int start   = fileContent.find("[", offset - 100);
  string tag = fileContent.substr(start, end);
  //regex exp("(\\[\\w+\\])(\?!OggS)");
  //regex exp("(\\[\\w{5,100}\\])(\?!OggS)");
  //regex exp("(\\[\\w+\\])\\.{1}(\?!OggS)");
  //regex exp("(\\[\\w+\\])(\\.{1}\\|\\R)?(\?!OggS)");
  //regex exp("(\\[\\w+\\])(\\.{1}\\|\\R)?(?!OggS)");
  //regex exp("(\\[\\w{5,100}\\])(\\.{1}\\|\\R)?(?!OggS)");
  regex exp("(\\[\\w+\\])");

  string soundTag = "";
  smatch match;
  if (regex_search(tag, match, exp)) 
    soundTag = match[0]; // tag = [audio02].ogg
    //soundTag += match[0]; // tag = [audio02].ogg
  
  //string result = soundTag;
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
  file.seekg(0, ios::beg);
  file.close();

  string audioContent = readFile(filepath, audioOffset);
  //string soundTag     = findSoundTag(audioContent, audioOffset) + ".ogg"; 
  string soundTag     = findSoundTag(filepath, audioOffset) + ".ogg"; 
  fmt::print("Sound tag: \t\t\t\t{}\t\n", soundTag);

  ofstream audioFile(soundTag.c_str(), ifstream::out | ifstream::binary); 
  audioFile.write(audioContent.c_str(), audioContent.length());

  audioFile.close();

   return 0;
}
