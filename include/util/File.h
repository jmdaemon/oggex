#pragma once
#ifndef FILE_H
#define FILE_H

#include <algorithm>
#include <string>
#include <filesystem>
#include <map>
#include <initializer_list>
#include <fstream>
#include <sstream>
#include <vector>

#include <fmt/core.h>

extern "C" {
#include <file.h>
  bool file_exists(const char* path);
  off_t file_size (const char* filename);
  bool under_limit(const char* path, off_t size);
  char* read_file(const char* path);
  char* read_slice(const char* path, off_t beg, off_t end);
}

const off_t MAX_FILE_SIZE = 1024 * 1024 * 4; 

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

std::string dataToString(std::filesystem::path filepath, off_t beg = 0, off_t end = 0);
void clean(std::initializer_list<std::filesystem::path> filepaths);

#endif
