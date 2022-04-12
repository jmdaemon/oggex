#include "File.h"

bool File::File::isFile(std::string file) {
  std::string ext = (std::filesystem::path (file)).extension();
  std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c ) { return std::tolower(c); }); 
  for (size_t i = 0; i < this->FileExtensions.size(); i++) {
    if (this->FileExtensions.at(i) == ext) { return true; }
  }
  return false;
}

bool File::File::isValid(std::string file) { return isFile(file); }
bool File::File::isValid(std::filesystem::path filepath) { return isFile(filepath.string()); }

std::string dataToString(std::filesystem::path filepath, off_t beg, off_t end) { 
  const std::string slice = read_slice(filepath.c_str(), beg, end);
  return slice;
}

void clean(std::initializer_list<std::filesystem::path> filepaths) {
  for(auto filepath: filepaths) { std::filesystem::remove(filepath); }
} 
