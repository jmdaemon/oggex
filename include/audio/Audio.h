#ifndef AUDIO_H
#define AUDIO_H

#include <filesystem>
#include <map>
#include <string>

namespace Audio {
  const static std::map<int, std::string> FileExtensions = {
    {0, ".ogg"},
  };

  struct AudioData {
    int audioQuality;
    bool lowQuality;
    std::string soundTag;
    std::filesystem::path audioFile;
    std::filesystem::path tempAudioFile;
    std::filesystem::path tempLogFile;
  };
}

#endif
