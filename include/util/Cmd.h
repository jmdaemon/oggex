#ifndef CMD_H
#define CMD_H

#include <map>
#include <string>
#include <filesystem>
#include <iostream>
#include <regex>

#include <fmt/core.h>

#include "Audio.h"
#include "Image.h"

void showUsage(std::string programName);
std::map<int, std::string> parseOptions(int argc, char** argv, bool bestQuality);
bool isEmpty(std::string arg, std::string errorMsg);

#endif
