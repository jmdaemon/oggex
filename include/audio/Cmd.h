#ifndef CMD_H
#define CMD_H

#include <map>
#include <string>

void showUsage(std::string programName);
std::map<int, std::string> parseOptions(int argc, char** argv, bool bestQuality);

#endif
