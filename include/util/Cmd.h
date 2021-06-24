#pragma once
#ifndef CMD_H
#define CMD_H

#include <string>
#include <map>
#include <tuple>

#include <fmt/core.h>

void showUsage(std::string programName);
bool isEmpty(std::string arg, std::string errorMsg);
void formatPrintUsage(std::map<int, std::tuple<std::string, std::string, std::string>> flags);

#endif
