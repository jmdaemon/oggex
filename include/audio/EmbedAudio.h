#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include <string>
#include <filesystem>
#include <cstdint>

#include "FileType.tpp"
std::string toLowerCase(const std::filesystem::path& filePath);
void showUsage(std::string programName);
std::map<int, std::string> parseOptions(int argc, char** argv);
bool isImage(std::filesystem::path filepath);
bool imageUnder4MiB (std::uintmax_t imageFileSize);

int embed(std::filesystem::path audioFilePath, std::filesystem::path imageFilePath, bool quality);

#endif
