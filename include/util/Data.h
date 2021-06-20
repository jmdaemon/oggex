#pragma once
#ifndef DATA_H
#define DATA_H

#include <cmath>

#include "Audio.h"
#include "Image.h"
#include "Options.h"

struct Data {
  public:
    Audio::AudioData audio{};
    Image::ImageData image{};
    Options options{};
};

Data createEmbedData(Audio::AudioData audio, Image::ImageData image, Options options);
Data createExtractData(Image::ImageData image, Options options);

std::string formatBytes(Data& data, size_t bytes, unsigned int decimals = 2);

#endif

