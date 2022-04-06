#pragma once
#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include "Image.h"
#include "Audio.h"
#include "Data.h"
#include "Mask.h"

#include <string>
#include <iosfwd>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <exception>
#include <fstream>

extern "C" {
#include <file.h>
  bool file_exists(const char* path);
  off_t file_size(const char* path);
#include <command.h>
  char* exec(const char* command, off_t size);
};

std::string createCommand(Data& data);
std::string encode(const std::string cmd, Data& data);

std::string encodeAudio(Data& data, bool decreaseQuality = false);
void encodeImage(Data& data);
int embed(Data& data);

#endif
