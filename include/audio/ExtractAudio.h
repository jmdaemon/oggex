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
#include "FileType.tpp"

size_t getFileSize(Data& data, size_t offset = 0);
std::string readFile(Data& data, size_t offset);
size_t getOffset(std::filesystem::path filepath, const char* searchTerm = "OggS");
std::string findSoundTag(Data& data, std::string fileData, size_t offset);
int extract(Data data);

void printSize(std::string key, std::string value);
void printSize(Data& data, std::tuple<std::string, size_t> sizeTuple, unsigned int leftPadding, unsigned int rightPadding);
#endif
