#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include <string>
#include <filesystem>

std::string toLowerCase(const std::filesystem::path& filePath);
void showUsage(std::string programName);

#endif
