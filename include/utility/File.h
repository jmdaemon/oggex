#pragma once
#ifndef FILE_CPP_H
#define FILE_CPP_H

#include <file.h>

#include <algorithm>
#include <string>
#include <filesystem>
#include <map>
#include <initializer_list>
#include <fstream>
#include <sstream>
#include <vector>
#include <fmt/core.h>

const off_t MAX_FILE_SIZE = 1024 * 1024 * 4; 

namespace File {
  class File { 
    private: 
      std::map<int, std::string> FileExtensions;
  };
}

std::string dataToString(std::filesystem::path filepath, off_t beg = 0, off_t end = 0);
void clean(std::initializer_list<std::filesystem::path> filepaths);

#endif
