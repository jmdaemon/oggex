#include "Audio.h"

void Audio::AudioData::decreaseQuality(unsigned int subtrahend) {
  this->setAudioQuality(this->getAudioQuality() - subtrahend);
  fmt::print("Decreasing quality. Quality = {}\n", this->getAudioQuality());
}

std::string formatSoundTag(std::string tag) { return ("[" + tag + "]"); }

Audio::AudioData createAudioData(std::string soundTag, std::filesystem::path audioFile) { return Audio::AudioData(soundTag, audioFile); }
