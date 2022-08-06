#pragma once
#ifndef OGGEX_H
#define OGGEX_H

#include "media.h"

#include <file.h>
#include <command.h>
#include "Audio.h"
#include "Data.h"
#include "Mask.h"
#include "Cmd.h"

#include <fmt/core.h>

#include <string>
#include <iosfwd>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <exception>
#include <fstream>

/** Constants */

static const off_t MAX_FILE_POST_SIZE = 1024 * 1024 * 4; // 4MiB

/** Supported image extensions */
static const char* ImageExtensions[] = {
  "jpg",
  "jpeg",
  "gif",
  "png",
  "webm"
};


std::string dataToString(std::filesystem::path filepath, off_t beg = 0, off_t end = 0);

std::string createCommand(Media& media);
std::string encode(const std::string cmd, Media& media);

int embed(Media& media);
std::string encodeAudio(Media& media, bool decreaseQuality = false);
void encodeImage(Media& media);

//size_t getFileSize(Data& data, size_t offset = 0);
//std::string readFile(Data& data, size_t offset);
size_t getOffset(std::filesystem::path filepath, const char* searchTerm = "OggS");
//std::string findSoundTag(Data& data, std::string fileData, size_t offset);
std::string findSoundTag(Media& media, std::string fileData, size_t offset);
int extract(Media& media); 


#endif // OGGEX_H
