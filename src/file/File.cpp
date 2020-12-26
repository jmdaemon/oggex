#include <iostream>
#include <string>
#include <filesystem>
#include <map>
#include <fstream>

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


