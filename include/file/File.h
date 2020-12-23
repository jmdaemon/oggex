#ifndef FILE_H
#define FILE_H

#include <string>
#include <filesystem>
#include <map>
#include <cstdint>

namespace File {
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

  bool fileUnder4MiB (uintmax_t fileSize, std::string errorMsg = "File too large to fit sounds.") {
    uintmax_t maxFileSize = 1024 * 1024 * 4; // About 4MB or exactly 4MiB
    if (fileSize > maxFileSize) {
      std::cerr << errorMsg << std::endl;
      return false;
    } else
    return true;
  } 
}

#endif
