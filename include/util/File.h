#ifndef FILE_H
#define FILE_H

#include <algorithm>
#include <string>
#include <filesystem>
#include <map>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <fstream>

#include <fmt/core.h>

namespace File {
  std::string toLowerCase(const std::filesystem::path& filePath);
  std::string getFileExtension(std::string file);
  bool isFile(std::string file, const std::map<int, std::string> FileExtensions);

  class File {
    public:
    virtual bool isValid(std::string file) = 0;
    virtual bool isValid(std::filesystem::path filepath) = 0;
  };
}

size_t sizeOf(std::ifstream& file);
size_t sizeOf(std::filesystem::path filepath);

std::string dataToString(std::ifstream& file);
bool under4MiB (std::filesystem::path filepath, std::string errorMsg = "File too large to fit sounds.");
bool fileExists(std::filesystem::path filepath);
void clean(std::initializer_list<std::filesystem::path> filepaths);

#endif
