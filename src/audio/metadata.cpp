#include "metadata.hpp"

#include <string>

AudioMetadata::AudioMetadata (std::string tag, int offset, int length) {
  setTag(tag);
  setOffset(offset);
  setLength(length);
};

