#pragma once
#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include <exception>
#include <filesystem>
#include <fstream>
#include <string>

#include "Image.h"
#include "Audio.h"
#include "Data.h"
#include "Mask.h"

std::string createCommand(Data& data);
std::string exec(const std::string cmd, Data& data);

std::string encodeAudio(Data& data, bool decreaseQuality = false);
void encodeImage(Data& data);
int embed(Data& data);

#endif
