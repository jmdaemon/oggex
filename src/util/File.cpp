#include <iostream>
#include <string>
#include <filesystem>
#include <map>
#include <fstream>
#include <initializer_list>

#include <fmt/core.h>

#include "File.h"

namespace File {
  std::string toLowerCase(const std::filesystem::path& filePath) {
    std::string fpath = filePath.string();
    std::transform(fpath.begin(), fpath.end(), fpath.begin(), 
        [](unsigned char c ) { return std::tolower(c); }); 
    return fpath;
  }

  std::string getFileExtension(std::string file) {
    return (std::filesystem::path (file)).extension();
  }

  bool isFile(std::string file, const std::map<int, std::string> FileExtensions) {
    std::string extension = toLowerCase(getFileExtension(file));
    for (int i = 0; i < FileExtensions.size(); i++) {
      if(FileExtensions.at(i) == extension) {
        return true;
      }
    }
    return false;
  }
}

size_t sizeOf(std::ifstream& file) {
  file.seekg(0, std::ios::end);
  size_t file_size = file.tellg();
  file.seekg(0, std::ios::beg);
  return file_size;
}

size_t sizeOf(std::filesystem::path filepath) {
  std::ifstream file(filepath, std::ifstream::in | std::ifstream::binary);
  return sizeOf(file); 
}

bool under4MiB (std::filesystem::path filepath, std::string errorMsg) {
  size_t fileSize = sizeOf(filepath);
  size_t maxFileSize = 1024 * 1024 * 4; // About 4MB or exactly 4MiB
  if (fileSize > maxFileSize) {
    std::cerr << errorMsg << std::endl;
    return false;
  } else
  return true;
} 

std::string dataToString(std::ifstream& file) {
  std::ostringstream fileContents;
  fileContents << file.rdbuf();
  std::string filedata = fileContents.str();
  return filedata;
}

bool fileExists(std::filesystem::path filepath) { 
  std::ifstream file(filepath, std::ifstream::in | std::ifstream::binary);
  if (!file.is_open()) {
    fmt::print(stderr, "Error: couldn't open \"{}\"\n", filepath.string());
    file.close();
    return false; 
  } 
  file.close();
  return true; 
}

void clean(std::initializer_list<std::filesystem::path> filepaths) {
  for( auto filepath: filepaths) {
    std::filesystem::remove(filepath);
  }
}

