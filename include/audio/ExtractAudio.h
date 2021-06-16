#ifndef EXTRACTAUDIO_H
#define EXTRACTAUDIO_H

#include <filesystem>
#include <fstream>
#include <string>
#include <exception>
#include <regex>

#include <fmt/core.h>

#include "Audio.h"
#include "Image.h"
#include "Data.h"
#include "FileType.tpp"

size_t getFileSize(std::ifstream& file);
std::string dataToString(std::ifstream& file);
size_t getAudioOffset(std::ifstream& file, const char* search_term = "OggS");
std::string readFile(std::filesystem::path filepath, size_t offset);
std::string findSoundTag(std::filesystem::path filepath, size_t offset);
int extract(std::filesystem::path filepath);

#endif
