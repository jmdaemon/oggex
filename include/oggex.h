#pragma once
#ifndef OGGEX_H
#define OGGEX_H

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

// Imports
#include "cli.h"
#include "media.h"
#include "ogxlog.h"

// Standard Library
#include <algorithm>
#include <array>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>

// Third Party Libraries
#include <file.h>
#include <command.h>
#include <spdlog/spdlog.h>

// Constants
static const off_t MAX_FILE_POST_SIZE = 1024 * 1024 * 4; // 4MiB
static const char* OGG_ID_HEADER = "OggS"; // Audio ID header present in .ogg files
static const char* PNG_ID_FOOTER = "IEND"; // Audio ID header present in .png files

// Embed
std::string format_command(Media& media);
void encode(const std::string cmd, Media& media);
void encodeAudio(Media& media);
void encodeImage(Media& media);
int embed(Media& media);

// Extract
std::string find_sound_tag(std::string conts);
int extract(Media& media); 

// Mask
std::array<char, 512> hashFile(std::array<char, 512> buffer, size_t count);

#endif // OGGEX_H
