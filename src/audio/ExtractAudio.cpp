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

//string getSoundTag(fs::path filepath, size_t firstBracket, size_t secondBracket) {
string getSoundTag(fs::path filepath) {
  ifstream file(filepath, ifstream::in | ios::binary);

  size_t firstBracket   = getAudioOffset(file, "[");
  size_t secondBracket  = getAudioOffset(file, "]");
  
  stringstream content;
  content << file.rdbuf();
  file.close();
  string fileContent = content.str();

  string soundTag = fileContent.substr(firstBracket, secondBracket);

  //string result = ""; 
  char* result = new char[soundTag.length()];
  for(int i = 0; i < soundTag.length(); i++) {
    result[i] = static_cast<char>(soundTag[i]);
    //result += static_cast<char>(std::stoi(soundTag[i], nullptr, 2) + 64);
  }
  return string(result);
}

//string findSoundTag(string file) {
  //int start = 0;
  //int end = 0;
  //string soundTag = "";
  //for (int i = 0; i < file.length(); i++) {
    //if (file[i] == '[')
      //start = i;
      ////end = i;
    //if (file[i] == ']')
      //end = i;
      ////start = i;
  //}

  //if (start != 0 && end != 0) {
    //soundTag = file.substr(start, end);
  //}

  //string result = "";
  //result.reserve(100); // Max tag length
  //regex exp("(\\w)");

  //smatch match;
  //for (int i = 0; i < soundTag.length(); i++) {
  ////if (regex_match(soundTag[i], match, exp)) 
  //if (regex_search(soundTag, match, exp))
    //result += match[i];
  //}

  //return result;
//}

//string findSoundTag(string file) {

string tail(string const& source, size_t const length) {
  if (length >= source.size()) { return source; }
  return source.substr(source.size() - length);
} 

//string findSoundTag(fs::path filepath) {
string findSoundTag(fs::path filepath, size_t offset) {
  ifstream file(filepath, ifstream::in | ios::binary);

  file.seekg(0, ios::end);
  size_t file_size = file.tellg();
  //size_t index = file_size - 100;

  file.seekg(0, ios::beg);

  stringstream content;
  content << file.rdbuf();
  file.close();
  string fileContent = content.str();

  //size_t fileContentSize = fileContent.size();
  //size_t index = fileContentSize - 100;
  //size_t fileContentSize = offset;
  //size_t index = fileContentSize - 100;
  size_t fileContentSize = offset;
  //size_t index = fileContentSize - (10 * 4);
  //size_t index = fileContentSize - 16;
  size_t index = fileContentSize - 10;
  //string tag = fileContent.substr(fileContent.length() - 100, fileContent.length());
  //string tag = tail(fileContent, 100);
  //string tag = fileContent.substr(file_size - 100, file_size);
  //string tag = fileContent.substr(file_size - 100, file_size);
  //string tag = fileContent.substr(index, fileContentSize);
  //string soundTag = file.substr(start, end);


  //string tag = fileContent.substr();
  //int start = tag.find("[");
  //int end   = tag.find("]");
  int start = fileContent.find("[", index);
  int end   = fileContent.find("]", index);
  string tag = fileContent.substr(start, end);
  //regex exp("(\\w)OggS");
  //regex exp(R"((\[)\w+(\]))(?!OggS)");
  //regex exp("((\\[)\\w+(\\]))(?!OggS)");
  //regex exp(R"((\[)\\w+(\]))(?!OggS)");
  //regex exp("((\\[)\\w+(\\]))(\?!OggS)");
  regex exp("(\\[\\w+\\])(\?!OggS)");

  string result = "";
  //char* result = new char[tag.length()];
  //result.reserve(tag.length());

  smatch match;
  //for (int i = 0; i < tag.length(); i++) {
  if (regex_search(tag, match, exp))
    //result[i] = static_cast<char>(match[i]);
    //result += static_cast<char>(match[i]);
    result += match[0];
    //result += match[i]; 
  //}
  //return string(result);

  return result;


  //string soundTag = "";
  //int start = 0;
  //int end = 0;
  //for (int i = 0; i < tag.length(); i++) { 
    //if (tag[i] == '[')
      //start = i;
      ////end = i;
    //if (tag[i] == ']')
      //end = i;
      ////start = i; 
  //}

  //if (start != 0 && end != 0) {
    ////soundTag = tag.substr(start, end);
    //soundTag = tag.substr(start, end);
  //}

  //string result = "";

  //for (int i = 0; i < soundTag.length(); i++) { 
    //result += static_cast<char>(soundTag[i]);
  //}

  //return result;

  //return soundTag;



  //sampletext

  ////int start = file.find("[");
  ////int end   = file.find("]");
  ////int headerStart = file.find("[");
  ////int headerEnd   = file.find("]");

  ////int start = file.find("[", headerStart  + 1);
  ////int end   = file.find("]", headerEnd    + 1);
  ////size_t length = fileContent.length() - 100;
  ////int start = fileContent.find("[", length);
  ////int end   = fileContent.find("]", length);
  //int start = tag.find("[");
  //int end   = tag.find("]");

  ////string soundTag = file.substr(start, end);
  //string soundTag = fileContent.substr(start, end);
  //regex exp("(\\w)");

  //string result = "";
  //result.reserve(soundTag.length());
  //smatch match;
  //for (int i = 0; i < soundTag.length(); i++) {
  //if (regex_search(soundTag, match, exp))
    ////result += static_cast<char>(soundTag[i] + 64);
    //result += match[i];
    ////result += static_cast<char>(soundTag[i]);
    ////result += static_cast<char>(stoi(soundTag[i], nullptr, 2) + 64);
    ////result += match[i];
  //}

  //return result;
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
  
  string soundTagStem = findSoundTag(filepath, audioOffset);
  string soundTag = (soundTagStem + ".ogg"); 
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

   // Filter file 
   return 0;

}
