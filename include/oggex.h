#pragma once
#ifndef OGGEX_H
#define OGGEX_H

// Imports
#include "media.h"
//#include "Data.h"
//#include "Cmd.h"

// Standard Library
#include <array>
#include <string>
#include <iosfwd>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <exception>

// Third Party Libraries
#include <file.h>
#include <command.h>
#include <fmt/core.h>

/** Constants */

static const off_t MAX_FILE_POST_SIZE = 1024 * 1024 * 4; // 4MiB

std::string dataToString(std::filesystem::path filepath, off_t beg = 0, off_t end = 0);

int embed(Media& media);

void encodeAudio(Media& media);
void encode(const std::string cmd, Media& media);
std::string format_command(Media& media);
void encodeImage(Media& media);

size_t getOffset(std::filesystem::path filepath, const char* searchTerm = "OggS");
std::string findSoundTag(Media& media, std::string fileData, size_t offset);
int extract(Media& media); 

// Mask
std::array<char, 512> hashFile(std::array<char, 512> buffer, size_t count);
void encodeTo(std::ifstream& inputFile, std::ofstream& outputFile, std::array<char, 512> buffer);

#endif // OGGEX_H
