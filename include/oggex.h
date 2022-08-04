#pragma once
#ifndef OGGEX_H
#define OGGEX_H

#include <file.h>
#include <command.h>
#include "Image.h"
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

std::string dataToString(std::filesystem::path filepath, off_t beg = 0, off_t end = 0);

std::string createCommand(Data& data);
std::string encode(const std::string cmd, Data& data);

std::string encodeAudio(Data& data, bool decreaseQuality = false);
void encodeImage(Data& data);
int embed(Data& data);

size_t getFileSize(Data& data, size_t offset = 0);
std::string readFile(Data& data, size_t offset);
size_t getOffset(std::filesystem::path filepath, const char* searchTerm = "OggS");
std::string findSoundTag(Data& data, std::string fileData, size_t offset);
int extract(Data data); 


#endif // OGGEX_H
