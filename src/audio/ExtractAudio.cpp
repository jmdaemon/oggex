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

//size_t getAudioOffset(ifstream& file, const char* search_term = "OggS") {
size_t getAudioOffset(ifstream& file, const char* search_term = "OggS") {
  file.seekg(0, ios::end);
  size_t file_size = file.tellg();
  fmt::print("\nSize of embedded file: \t\t{} bytes\n", file_size);

  file.seekg(0, ios::beg);

  ostringstream fileContents;
  fileContents << file.rdbuf();
  string filedata = fileContents.str();
  //string filedata = file_content.str();

  //std::string key = "\x39\xb5\x7d\xc6";
  //string searchTerm = "\0x4\0x67\0x67\0x53\0\2";
  //string searchTerm = "\x4\x67\x67\x53";
  size_t found_at = 0;
  found_at = filedata.find(search_term);
  //found_at = filedata.find(searchTerm);
  //auto result = search(begin(filedata), end(filedata), begin(searchTerm), end(searchTerm));
  //if (end(filedata) != result) {
    //found_at = result - filedata.begin();
  //}

  //string file_content;
  //file_content.reserve(file_size);
  //char buffer[16384];
  //streamsize chars_read;

  //while (file.read(buffer, sizeof buffer), chars_read = file.gcount())
      //file_content.append(buffer, chars_read);

  //size_t search_term_size = strlen(search_term);

  //size_t offset = 0; 
  //size_t found_at = 0;
  //if (file.eof()) { 
    //for (; file_size > offset && (found_at = file_content.find(search_term, offset)) != string::npos; 
        //offset = found_at + search_term_size)
      //break; 
  //}

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

  //fmt::print("File content: {}\n", content.str()); 
  return result;
}

//string getSoundTag(fs::path filepath, size_t firstBracket, size_t secondBracket) {
//string getSoundTag(fs::path filepath) {
  //ifstream file(filepath, ifstream::in | ios::binary);

  //size_t firstBracket   = getAudioOffset(file, "[");
  //size_t secondBracket  = getAudioOffset(file, "]");

  //file.seekg(firstBracket, ios::end);
  //ifstream::pos_type first = file.tellg();

  //file.seekg(secondBracket, ios::end);
  //ifstream::pos_type second = file.tellg();




  ////file.seekg(0, ios::end);
  ////size_t file_size = file.tellg(); 
//}

string findSoundTag(string file) {
  int start = 0;
  int end = 0;
  string soundTag = "";
  for (int i = 0; i < file.length(); i++) {
    if (file[i] == '[')
      start = i;
      //end = i;
    if (file[i] == ']')
      end = i;
      //start = i;
  }

  if (start != 0 && end != 0) {
    soundTag = file.substr(start, end);
  }

  string result = "";
  //result.reserve(100); // Max tag length
  result.reserve(50);
  //const regex regexp(R"(\w)(_)?");
  //const regex regexp("(\\w)(_)?");
  //regex regexp("(\\w)(_)?");
  //regex exp("(\\w)(_)?");
  regex exp("(\\w)");

  //if ( regex_match ( regexp.begin(), regexp.end(), soundTag ) )
    //result.append();

  smatch match;
  //if (regex_search(soundTag.begin(), soundTag.end(), match, regexp))
  //if (regex_search(begin(soundTag), end(soundTag), match, regexp))
  //if (regex_search(soundTag.begin(), soundTag.end(), match, exp))
  for (int i = 0; i < soundTag.length(); i++) {
  //if (regex_match(soundTag[i], match, exp)) 
  if (regex_search(soundTag, match, exp))
    result += match[i];
  }
  //for (const auto &tag : soundTag) { 
    ////if (regex_match(tag, match, regexp)) {
    ////if (regex_search(tag, match, regexp)) {
    //if (regex_match(soundTag, match, regexp)) {
      //result += match.str();
    //}
  //}

  
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

  //tempFile << soundTagStem;
  tempFile.close();
  //fs::path tempfilepath = "temp.ogg";
  //ofstream tempFile();

  //fs::path tempfilepath = "temp.ogg";

  //ofstream outputFile(tempfilepath, ifstream::out | ifstream::binary);
  //outputFile << audioContent;
  //outputFile.close();
  //fmt::print("audioContent string: {}\n", audioContent);
  string audioContent = readFile(filepath, audioOffset);
  assert(!audioContent.empty());

  //string soundTag = fmt::format("{}.ogg", findSoundTag(audioContent)); 

  //string soundTag = (findSoundTag(audioContent) + ".ogg"); 
  //ifstream tempFile(tempfilepath, ifstream::in | ifstream::binary);

  //ostringstream soundTagContent;
  //soundTagContent << tempFile.rdbuf();
  //tempFile.close();

  //string soundTagStem = soundTagContent.str();

  //std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  //const std::wstring wide_string = L"This is a string";
  //const std::string utf8_string = converter.to_bytes(wide_string);

  //string soundTagStem = u8 + getSoundTag(audioContent);

  //fs::path tempfilepath = "temp.ogg";

  //ofstream tempFile(tempfilepath, ifstream::out | ifstream::binary);
  //tempFile << soundTagStem;
  //tempFile.close();
  
  //ostringstream soundTagContent;
  //soundTagContent << soundTagStem;
  //tempFile.close();


  //string soundTag = (getSoundTag(tempfilepath) + ".ogg"); 
  //std::string base64_decode(findSoundTag(audioContent), false);
  //string soundTag = (findSoundTag(audioContent) + ".ogg"); 
  //string soundTagStem = base64_decode(findSoundTag(audioContent));
  string soundTagStem = findSoundTag(audioContent);
  string soundTag = (soundTagStem + ".ogg"); 
  //string soundTag = (base64_decode(findSoundTag(audioContent), false) + ".ogg"); 
  //string soundTag = (soundTagStem + ".ogg"); 
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
