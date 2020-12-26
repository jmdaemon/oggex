#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include <string>
#include <filesystem>
#include <cstdint>

#include "FileType.tpp"

int embed(std::filesystem::path audioFilePath, std::filesystem::path imageFilePath, bool quality);

#endif
