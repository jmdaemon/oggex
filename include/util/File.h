#ifndef FILE_H
#define FILE_H

#include <algorithm>
#include <string>
#include <filesystem>
#include <map>
#include <initializer_list>
#include <fstream>

#include <fmt/core.h>

const size_t MAX_FILE_SIZE = 1024 * 1024 * 4; 

namespace File {
  std::string toLowerCase(const std::filesystem::path& filePath);
  std::string getFileExtension(std::string file);

  class File {
    public:
    virtual bool isValid(std::string file) = 0;
    virtual bool isValid(std::filesystem::path filepath) = 0;
    bool isFile(std::string file, const std::map<int, std::string> FileExtensions);
  };
}

size_t sizeOf(std::ifstream& file, size_t offset = 0);
size_t sizeOf(std::filesystem::path filepath, size_t offset = 0);

std::string dataToString(std::filesystem::path filepath, size_t offset = 0);
std::string readFile(std::filesystem::path filepath, size_t start, size_t end);
bool under4MiB (std::filesystem::path filepath, std::string errorMsg = "File too large to fit sounds.");
bool fileExists(std::filesystem::path filepath);
void clean(std::initializer_list<std::filesystem::path> filepaths);
void writeToDisk(std::filesystem::path outputFileName, std::string outputData);

#endif
