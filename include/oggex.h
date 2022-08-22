#pragma once
#ifndef OGGEX_H
#define OGGEX_H

// Imports
#include "media.h"
#include "cli.h"
#include "ogxlog.h"

// Standard Library
#include <algorithm>
#include <array>
#include <string>
#include <iosfwd>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <exception>
#include <memory>
#include <vector>

// Third Party Libraries
#include <file.h>
#include <command.h>
#include <spdlog/spdlog.h>

// Constants
static const off_t MAX_FILE_POST_SIZE = 1024 * 1024 * 4; // 4MiB
static const char* OGG_ID_HEADER = "OggS"; // Audio ID header present in .ogg files
static const char* PNG_ID_FOOTER = "IEND"; // Audio ID header present in .png files

// Embed
int embed(Media& media);

void encodeAudio(Media& media);
void encode(const std::string cmd, Media& media);
std::string format_command(Media& media);

// Extract
void encodeImage(Media& media);

std::string find_sound_tag(std::string conts);
int extract(Media& media); 

// Mask
std::array<char, 512> hashFile(std::array<char, 512> buffer, size_t count);
void encodeTo(std::ifstream& inputFile, std::ofstream& outputFile, std::array<char, 512> buffer);

#endif // OGGEX_H
