#pragma once
#ifndef EXTRACTAUDIO_H
#define EXTRACTAUDIO_H

#include <filesystem>
#include <fstream>
#include <string>

#include <fmt/core.h>

#include "Audio.h"
#include "Image.h"
#include "Data.h"
#include "Cmd.h"

extern "C" {
#include <file.h>
  off_t file_size(const char* path);
};

size_t getFileSize(Data& data, size_t offset = 0);
std::string readFile(Data& data, size_t offset);
size_t getOffset(std::filesystem::path filepath, const char* searchTerm = "OggS");
std::string findSoundTag(Data& data, std::string fileData, size_t offset);
int extract(Data data); 
#endif
