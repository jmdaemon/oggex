#pragma once
#ifndef CMD_H
#define CMD_H

#include <string>

#include <fmt/core.h>

void showUsage(std::string programName);
bool isEmpty(std::string arg, std::string errorMsg);

#endif
