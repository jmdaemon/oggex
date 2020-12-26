#ifndef CMD_H
#define CMD_H

#include <map>
#include <string>
//std::string toLowerCase(const std::filesystem::path& filePath);
void showUsage(std::string programName);
std::map<int, std::string> parseOptions(int argc, char** argv, bool bestQuality);
//bool isImage(std::filesystem::path filepath);
//bool imageUnder4MiB (std::uintmax_t imageFileSize);

#endif
