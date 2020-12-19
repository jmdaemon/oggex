#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include <string>
#include <filesystem>
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

template<typename FileType>
bool isCorrupted(std::filesystem::path filepath, FileType& file) {
  if (!file.is_open()) {
    fmt::fprintf(std::cerr, "Error: couldn't open \"%s\"", filepath);
    return true;
  } else
    return false;
}

#endif
