#include "Data.h"

Data createEmbedData(Audio::AudioData audio, Image::ImageData image, Options options) { 
  return Data{ .audio = audio, .image = image, .options = options};
}

Data createExtractData(Image::ImageData image, Options options) {
  return Data{ .image = image, .options = options};
}

void rename(Data& data, std::string outputFile, std::string from, std::string to) {
  if (data.options.isEnabled(outputFile)) {
    std::filesystem::rename(std::filesystem::path(from), std::filesystem::path(to));
    data.options.setFileName(outputFile, std::filesystem::path(to));
  }
}
