#ifndef AUDIO_H
#define AUDIO_H

#include <filesystem>
#include <map>
#include <string>

#include "File.h"

namespace Audio {
  const static std::map<int, std::string> FileExtensions = {
    {0, ".ogg"},
  };
  const static int  DEFAULT_AUDIO_QUALITY             = 10;
  const static bool ENABLE_LOW_QUALITY                = false;
  const static std::filesystem::path TEMP_AUDIO_FILE  = "out.ogg";
  const static std::filesystem::path TEMP_LOG_FILE    = "Log.txt";
  
  struct AudioData {
    AudioData(std::string soundTag, std::filesystem::path audioFile) : 
      audioQuality(DEFAULT_AUDIO_QUALITY), lowQuality(ENABLE_LOW_QUALITY), 
      soundTag(soundTag), audioFile(audioFile),
      tempAudioFile(TEMP_AUDIO_FILE), tempLogFile(TEMP_LOG_FILE),
      fileSize(getFileSize(audioFile))
    {}

    AudioData():
      audioQuality(DEFAULT_AUDIO_QUALITY), lowQuality(ENABLE_LOW_QUALITY), 
      soundTag(""), audioFile(""),
      tempAudioFile(TEMP_AUDIO_FILE), tempLogFile(TEMP_LOG_FILE),
      fileSize(0)
    {}

    int audioQuality;
    bool lowQuality;
    std::string soundTag;
    std::filesystem::path audioFile;
    std::filesystem::path tempAudioFile;
    std::filesystem::path tempLogFile;
    size_t fileSize;
  };

  bool isAudio(std::string file);
  bool isAudio(std::filesystem::path filepath);
}
Audio::AudioData createAudioData(std::string soundTag, std::filesystem::path audioFile);
Audio::AudioData createAudioData();

#endif
