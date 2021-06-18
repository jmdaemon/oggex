#pragma once
#ifndef MASK_H
#define MASK_H

#include <array>
#include <fstream>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <memory>
#include <string>

#include <fmt/core.h>

std::array<char, 512> hashFile(std::array<char, 512> buffer, size_t count);
void encodeTo(std::ifstream& inputFile, std::ofstream& outputFile, std::array<char, 512> buffer);


#endif
