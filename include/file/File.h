#ifndef FILE_H
#define FILE_H

#include <algorithm>
#include <string>
#include <filesystem>
#include <map>
#include <cstdint>

namespace File {
  std::string toLowerCase(const std::filesystem::path& filePath);
  std::string getFileExtension(std::string file);
  bool isFile(std::string file, const std::map<int, std::string> FileExtensions);
  bool fileUnder4MiB (uintmax_t fileSize, std::string errorMsg = "File too large to fit sounds.");

}

size_t getFileSize(std::filesystem::path filepath);
bool under4MiB (std::filesystem::path filepath, std::string errorMsg = "File too large to fit sounds.");

#endif
