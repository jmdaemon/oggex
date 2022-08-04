#include "File.h"

std::string dataToString(std::filesystem::path filepath, off_t beg, off_t end) { 
  const std::string slice = read_slice(filepath.c_str(), beg, end);
  return slice;
}

void clean(std::initializer_list<std::filesystem::path> filepaths) {
  for(auto filepath: filepaths) { std::filesystem::remove(filepath); }
} 
