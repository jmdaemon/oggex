#pragma once
#ifndef DATA_H
#define DATA_H

#include "file.h"
#include <gmpxx.h>
#include <bytesize.h>

//#include "Audio.h"
#include <map>
#include "Options.h"

#include <cmath>
#include <iosfwd>
#include <tuple>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>

#include <fmt/core.h>

struct Data {
  public:
    //Audio::AudioData audio{};
    //Image::ImageData image{};
    const char* image;
    Options options{};
};

//Data createEmbedData(Audio::AudioData audio, const char* image, Options options);
//Data createExtractData(const char* image, Options options);

void printSize(std::string key, std::string value, unsigned int leftPadding = 24, unsigned int rightPadding = 8);
void printSize(Data& data, std::tuple<std::string, size_t> sizeTuple, unsigned int leftPadding, unsigned int rightPadding = 8);

void printEmbedSizes(Data& data, size_t maxFileSize, size_t tempFileSize, size_t imageFileSize, size_t soundTagSize, size_t finalSize);
void printExtractSizes(Data& data, size_t embeddedFileSize, size_t audioFileSize, size_t audioOffset);
#endif

