#include "Audio.h"

namespace Audio {
  bool isAudio(std::string file) { return File::isFile(file, FileExtensions); }
  bool isAudio(std::filesystem::path filepath) { return File::isFile(filepath.string(), FileExtensions); }

  bool Audio::AudioData::isValid(std::string file) { return isAudio(file); }
  bool Audio::AudioData::isValid(std::filesystem::path filepath) { return isAudio(filepath); }
}

std::string formatSoundTag(std::string tag) { return ("[" + tag + "]"); }
Audio::AudioData createAudioData(std::string soundTag, std::filesystem::path audioFile) { return Audio::AudioData(soundTag, audioFile); }
Audio::AudioData createAudioData() { return Audio::AudioData("", ""); }
