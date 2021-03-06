#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include <filesystem>
#include <map>
#include <string>

#include "File.h"

namespace Audio {
  const static int  DEFAULT_AUDIO_QUALITY             = 10;
  const static bool ENABLE_LOW_QUALITY                = false;
  const static std::filesystem::path TEMP_AUDIO_FILE  = "out.ogg";
  const static std::filesystem::path TEMP_LOG_FILE    = "Log.txt";
  
  class AudioData : public File::File {
    private: 
      std::map<int, std::string> FileExtensions = { 
        {0, ".ogg"}, 
      };
    int audioQuality;
    bool monoAudio;
    std::string soundTag;
    std::filesystem::path audioFile;
    std::filesystem::path tempAudioFile;
    std::filesystem::path tempLogFile;
    size_t fileSize;

    public:
    AudioData(std::string soundTag = "", std::filesystem::path audioFile = "") : 
      audioQuality(DEFAULT_AUDIO_QUALITY), monoAudio(ENABLE_LOW_QUALITY), 
      soundTag(soundTag), audioFile(audioFile),
      tempAudioFile(TEMP_AUDIO_FILE), tempLogFile(TEMP_LOG_FILE),
      fileSize(sizeOf(audioFile))
    {}

    // Getters
    int getAudioQuality()                                   { return this->audioQuality; }
    bool getMonoAudio()                                     { return this->monoAudio; }
    std::string getSoundTag()                               { return this->soundTag; }
    std::filesystem::path getAudio()                        { return this->audioFile; }
    std::filesystem::path getTempAudio()                    { return this->tempAudioFile; }
    std::filesystem::path getTempLog()                      { return this->tempLogFile; }
    size_t getAudioFileSize()                               { return this->fileSize; }

    // Setters
    void setAudioQuality(int quality)                       { this->audioQuality = quality; }
    void setMonoAudio(bool quality)                         { this->monoAudio = quality; }
    void setSoundTag(std::string soundTag)                  { this->soundTag = soundTag; }
    void setAudio(std::filesystem::path audioFile)          { this->audioFile = audioFile; }
    void setTempAudio(std::filesystem::path tempAudioFile)  { this->tempAudioFile = tempAudioFile; }
    void setTempLog(std::filesystem::path tempLogFile)      { this->tempLogFile = tempLogFile; }
    void setAudioFileSize(size_t fileSize)                  { this->fileSize = fileSize; }

    void decreaseQuality(unsigned int subtrahend);
  };
}

std::string formatSoundTag(std::string tag);

Audio::AudioData createAudioData(std::string soundTag = "", std::filesystem::path audioFile = "");

#endif
