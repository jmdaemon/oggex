#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include <string>
#include <filesystem>
#include <map>

std::string toLowerCase(const std::filesystem::path& filePath);
void showUsage(std::string programName);
std::map<int, std::string> parseOptions(int argc, char** argv);

#endif
