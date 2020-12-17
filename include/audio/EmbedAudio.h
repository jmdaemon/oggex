#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include <string>
#include <filesystem>
#include <map>

std::string toLowerCase(const std::filesystem::path& filePath);
void showUsage(std::string programName);
/*std::tuple<std::filesystem::path, std::filesystem::path> parseOptions(int argc, char** argv);*/
/*std::map<std::filesystem::path, std::filesystem::path> parseOptions(int argc, char** argv);*/
/*std::map<int, std::filesystem::path> parseOptions(int argc, char** argv);*/
std::map<int, std::string> parseOptions(int argc, char** argv);

#endif
