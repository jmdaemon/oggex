#include <iostream>
#include <string>
#include <filesystem>
#include <exception>
#include <fstream>

#include <fmt/core.h>
#include <fmt/printf.h>

#include "EmbedAudio.h"

using namespace std;
namespace fs = std::filesystem;

int extract(fs::path filepath) {

  // Find section where ogg file begins.
  // Find audio tag, store in string
  // Slice image file into two
  // - Read the audio file path after the image file start, until file end
  // Write to new audio file with audio tag


  ifstream file(filepath, ifstream::in | ifstream::binary);
  if (isCorrupted(filepath, file)) { throw exception(); }

  file.seekg(0, ios::end);
  size_t file_size = file.tellg();

  file.seekg(0, ios::beg);
  string file_content;
  file_content.reserve(file_size);
  char buffer[16384];
  streamsize chars_read;

  while (file.read(buffer, sizeof buffer), chars_read = file.gcount())
      file_content.append(buffer, chars_read);


  const char* search_term = "Oggs";
  size_t search_term_size = strlen(search_term);

  size_t offset = 0, found_at;
  if (file.eof()) { 
    //for (std::string::size_type offset = 0, found_at; file_size > offset && (found_at = file_content.find(search_term, offset)) != std::string::npos; 
    for (; file_size > offset && (found_at = file_content.find(search_term, offset)) != string::npos; 
        offset = found_at + search_term_size)
      cout << found_at << endl;
  }


  // Filter file 
  return 0;

}
