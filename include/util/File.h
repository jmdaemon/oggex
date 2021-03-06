#pragma once
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
  class File { 
    private: 
      std::map<int, std::string> FileExtensions;

    public: 
      bool isValid(std::string file); 
      bool isValid(std::filesystem::path filepath);
      bool isFile(std::string file);
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
