#ifndef DATA_H
#define DATA_H

#include "Audio.h"
#include "Image.h"

struct Data {
  public:
    Audio::AudioData audio{};
    Image::ImageData image{};
    bool enableMonoAudio{};
    bool ignoreSizeLimit{};
    bool showDebugInfo{};
    bool setOutputFilename{};
    bool setAudioFilename{};
    bool setImageFilename{};
};
#endif
