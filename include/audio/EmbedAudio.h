#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include <string>
#include <filesystem>
#include <fstream>
#include <map>
#include <cstdint>
#include <fstream>

#include <fmt/core.h>
#include <fmt/printf.h>

std::string toLowerCase(const std::filesystem::path& filePath);
void showUsage(std::string programName);
std::map<int, std::string> parseOptions(int argc, char** argv);
bool isImage(std::filesystem::path filepath);
bool imageUnder4MiB (std::uintmax_t imageFileSize);

template<typename FileType> bool isCorrupted(std::filesystem::path filepath, FileType& file) {
  if (!file.is_open()) {
    fmt::fprintf(std::cerr, "Error: couldn't open \"%s\"", filepath);
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

int embed(int argc, char** argv);

#endif
