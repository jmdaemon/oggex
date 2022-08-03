#pragma once
#ifndef DATA_H
#define DATA_H

#include "file.h"
#include <gmpxx.h>
#include <bytesize.h>

#include "Audio.h"
#include "Image.h"
#include "Options.h"

#include <cmath>
#include <iosfwd>
#include <tuple>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>

struct Data {
  public:
    Audio::AudioData audio{};
    Image::ImageData image{};
    Options options{};
};

//struct ByteFormat {
  //std::string amount;
  //std::string unit;
//};

Data createEmbedData(Audio::AudioData audio, Image::ImageData image, Options options);
Data createExtractData(Image::ImageData image, Options options);

void printSize(std::string key, std::string value, unsigned int leftPadding = 24, unsigned int rightPadding = 8);
void printSize(Data& data, std::tuple<std::string, size_t> sizeTuple, unsigned int leftPadding, unsigned int rightPadding = 8);
//std::tuple<std::string, std::string> formatBytes(Data& data, size_t bytes, unsigned int decimals = 2);
//std::tuple<size_t, std::string> formatBytes(Data& data, size_t bytes, unsigned int decimals = 2);
//ByteFormat formatBytes(Data& data, size_t bytes, unsigned int decimals = 2);
Byte formatBytes(Data& data, size_t bytes, unsigned int decimals = 2);

void printEmbedSizes(Data& data, size_t maxFileSize, size_t tempFileSize, size_t imageFileSize, size_t soundTagSize, size_t finalSize);
void printExtractSizes(Data& data, size_t embeddedFileSize, size_t audioFileSize, size_t audioOffset);
#endif

