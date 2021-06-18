#ifndef DATA_H
#define DATA_H

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

void rename(Data& data, std::string outputFile, std::string from, std::string to);
#endif

