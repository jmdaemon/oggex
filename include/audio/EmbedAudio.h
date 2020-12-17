#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include <string>
#include <filesystem>
#include <tuple>

std::string toLowerCase(const std::filesystem::path& filePath);
void showUsage(std::string programName);
std::tuple<std::filesystem::path, std::filesystem::path> parseOptions(int argc, char** argv);

#endif
