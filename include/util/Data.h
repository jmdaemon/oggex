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
    //bool enableMonoAudio{};
    //bool ignoreSizeLimit{};
    //bool showDebugInfo{};
    //bool setOutputFilename{};
    //bool setAudioFilename{};
    //bool setImageFilename{};
};

//Data createEmbedData(Audio::AudioData audio, Image::ImageData image, bool enableMonoAudio, bool ignoreSizeLimit, bool showDebugInfo, bool setOutputFilename);
//Data createExtractData(Image::ImageData image, bool showDebugInfo, bool setAudioFilename, bool setImageFilename);

#endif

