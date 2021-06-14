#include <filesystem>
#include <fstream>
#include <map>
#include <string>

//#include <fmt/core.h>
//#include <fmt/printf.h> 
#include <fmt/format.h>

template<typename FileType> bool isCorrupted(std::filesystem::path filepath, FileType& file) {
  if (!file.is_open()) {
    //fmt::fprintf(std::cerr, "Error: couldn't open \"%s\"\n", filepath);
    return true;
  } else
    return false;
}

template<typename FileType>
std::string fileToString(FileType& filestream) {
  std::ostringstream fileContents;
  fileContents << filestream.rdbuf();
  return fileContents.str();
}

template<typename FileType>
int getFileSize(FileType& file) {
  std::ostringstream contents;
  contents << file.rdbuf(); // Read imageFileData
  contents.seekp(0, std::ios::end);
  int contentSize = contents.tellp();
  return contentSize;
}
