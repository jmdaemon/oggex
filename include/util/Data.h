#ifndef DATA_H
#define DATA_H

#include "Audio.h"
#include "Image.h"

struct Data {
  public:
    Audio::AudioData audio{};
    Image::ImageData image{};
};

#endif
