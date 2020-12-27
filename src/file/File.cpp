#include <iostream>
#include <string>
#include <filesystem>
#include <map>
#include <fstream>
#include <initializer_list>

#include <fmt/core.h>
#include <fmt/printf.h>

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
    std::string extension = toLowerCase(File::getFileExtension(file));
    for (int i = 0; i < FileExtensions.size(); i++) {
      if(FileExtensions.at(i) == extension) {
        return true;
      }
    }
    return false;
  }

  bool fileUnder4MiB (uintmax_t fileSize, std::string errorMsg) {
    uintmax_t maxFileSize = 1024 * 1024 * 4; // About 4MB or exactly 4MiB
    if (fileSize > maxFileSize) {
      std::cerr << errorMsg << std::endl;
      return false;
    } else
    return true;
  } 
}

size_t getFileSize(std::filesystem::path filepath) {
  std::ifstream file(filepath, std::ifstream::in | std::ifstream::binary);
  file.seekg(0, std::ios::end);
  size_t file_size = file.tellg();
  file.seekg(0, std::ios::beg);
  file.close();
  return file_size;
}
bool under4MiB (std::filesystem::path filepath, std::string errorMsg) {
  //uintmax_t fileSize = std::filesystem::file_size(filepath);
  //uintmax_t maxFileSize = 1024 * 1024 * 4; // About 4MB or exactly 4MiB
  size_t fileSize = getFileSize(filepath);
  size_t maxFileSize = 1024 * 1024 * 4; // About 4MB or exactly 4MiB
  if (fileSize > maxFileSize) {
    std::cerr << errorMsg << std::endl;
    return false;
  } else
  return true;
} 

size_t getFileSize(std::ifstream& file) {
  file.seekg(0, std::ios::end);
  size_t file_size = file.tellg();
  file.seekg(0, std::ios::beg);
  return file_size;
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
    fmt::fprintf(std::cerr, "Error: couldn't open \"%s\"\n", filepath);
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

