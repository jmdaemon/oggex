#include "Audio.h"

namespace Audio {
  bool Audio::AudioData::isValid(std::string file) { return File::isFile(file, FileExtensions); }
  bool Audio::AudioData::isValid(std::filesystem::path filepath) { return File::isFile(filepath.string(), FileExtensions); }
}

std::string formatSoundTag(std::string tag) { return ("[" + tag + "]"); }
bool tagUnder100(unsigned int tagLength) {
  unsigned int maxTagLength = 100;
  if (tagLength < maxTagLength) {
    return true;
  }
  return false;
}

Audio::AudioData createAudioData(std::string soundTag, std::filesystem::path audioFile) { return Audio::AudioData(soundTag, audioFile); }
Audio::AudioData createAudioData() { return Audio::AudioData("", ""); }
