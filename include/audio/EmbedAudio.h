#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include <string>
#include <filesystem>
#include <map>
#include <cstdint>

std::string toLowerCase(const std::filesystem::path& filePath);
void showUsage(std::string programName);
std::map<int, std::string> parseOptions(int argc, char** argv);
/*bool checkFileIsImage(int index, std::string arg);*/
/*int checkFile(std::filesystem::path filePath);*/
bool isImage(std::filesystem::path filepath);
bool imageUnder4MiB (std::uintmax_t imageFileSize);
/*bool imageNotCorrupted(std::filesystem::path imageFilePath);*/
bool imageIsCorrupted(std::filesystem::path imageFilePath);

#endif
