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
/*bool checkFileIsImage(int index, std::string arg);*/
/*int checkFile(std::filesystem::path filePath);*/
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
/*template<typename FileType>;*/
/*template bool isCorrupted<std::ifstream>(std::filesystem::path filepath, FileType file);*/
/*template bool isCorrupted<std::ofstream>(std::filesystem::path filepath, FileType file);*/
/*extern template bool isCorrupted(std::filesystem::path imageFilePath, FileType file);*/
/*bool imageNotCorrupted(std::filesystem::path imageFilePath);*/
/*bool imageIsCorrupted(std::filesystem::path imageFilePath);*/

#endif
