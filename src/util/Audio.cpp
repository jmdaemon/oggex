#include "Audio.h"

namespace Audio {
  bool Audio::AudioData::isValid(std::string file) { return isFile(file); }
  bool Audio::AudioData::isValid(std::filesystem::path filepath) { return isFile(filepath.string()); }
}

void Audio::AudioData::decreaseQuality(unsigned int subtrahend) {
  this->setAudioQuality(this->getAudioQuality() - subtrahend);
  fmt::print("Decreasing quality. Quality = {}\n", this->getAudioQuality());
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
