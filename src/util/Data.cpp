#include "Data.h"

#include <iosfwd>
#include <tuple>
#include <vector>
#include <sstream>
#include <string>

Data createEmbedData(Audio::AudioData audio, Image::ImageData image, Options options) { 
  return Data{ .audio = audio, .image = image, .options = options};
}

Data createExtractData(Image::ImageData image, Options options) {
  return Data{ .image = image, .options = options};
}

template<typename T>
std::string byteToString(T bytes, unsigned int dm = 10) {
    std::stringstream ss; 
    ss.precision(dm); 
    ss << bytes; 
    std::string byteString = ss.str();
    return byteString;
}

void printSize(std::string key, std::string value, unsigned int leftPadding, unsigned int rightPadding) { 
  fmt::print("{:<{}} : {:<{}}\n", key, leftPadding, value, rightPadding);
}

void printSize(Data& data, std::tuple<std::string, size_t> sizeTuple, unsigned int leftPadding, unsigned int rightPadding) { 
  auto sizeWithUnit = formatBytes(data, std::get<1>(sizeTuple)); 
  rightPadding = (!data.options.isReadableEnabled()) ? 8 : 4;
  fmt::print("{:<{}} : {:<{}} {}\n", std::get<0>(sizeTuple), leftPadding, std::get<0>(sizeWithUnit), rightPadding, std::get<1>(sizeWithUnit));
}

std::tuple<std::string, std::string> formatBytes(Data& data, size_t bytes, unsigned int decimals) {
    int unit = (data.options.isSIEnabled()) ? 1000 : 1024; 
    const unsigned int dm = (decimals < 0) ? 0 : decimals;
    std::map<int, std::string> sizes;
    if (data.options.isSIEnabled()) {
      sizes = {
        { 0, "Bytes"}, { 1, "KB"}, { 2, "MB"}, { 3, "GB"}, { 4, "TB"}, 
        { 5, "PB"}, { 6, "EB"}, { 7, "ZB"}, { 8, "YB"} }; 
    } else { 
      sizes = { 
        { 0, "Bytes"}, { 1, "KiB"}, { 2, "MiB"}, { 3, "GiB"}, { 4, "TiB"}, 
        { 5, "PiB"}, { 6, "EiB"}, { 7, "ZiB"}, { 8, "YiB"} }; 
    }

    if (!data.options.isReadableEnabled()) { 
      auto result = std::make_tuple(byteToString(bytes), sizes[0]);
      return result;
    } 

    const double i = floor(std::log(bytes) / std::log(unit)); 
    double res = (bytes / std::pow(unit, i)); 
    auto result = std::make_tuple(byteToString(res, dm), sizes[i]);
    return result;
}

void printEmbedSizes(Data& data, size_t maxFileSize, size_t tempFileSize, size_t imageFileSize, size_t soundTagSize, size_t finalSize) {
    std::map<int, std::tuple<std::string, size_t>> sizes = {
      { 0, std::make_tuple("Max File Size"  , maxFileSize)},
      { 1, std::make_tuple("Temp File Size" , tempFileSize)},
      { 2, std::make_tuple("Image File Size", imageFileSize)},
      { 3, std::make_tuple("Sound Tag Size" , soundTagSize)},
      { 4, std::make_tuple("Final Size"     , finalSize)}
    };

    fmt::print("\n================ File Sizes ================\n");
    for (auto const& [key, sizeTuple] : sizes)
      printSize(data, sizeTuple, 16); 
}

void printExtractSizes(Data& data, size_t embeddedFileSize, size_t audioFileSize, size_t audioOffset) {
  std::map<int, std::tuple<std::string, size_t>> sizes = {
      { 0, std::make_tuple("Size of Embedded File"  , embeddedFileSize)},
      { 1, std::make_tuple("Audio File Size"        , audioFileSize)},
      { 2, std::make_tuple("Audio File Offset"      , audioOffset)}
    };

    fmt::print("\n================ File Sizes ================\n"); 
    for (auto const& [key, sizeTuple] : sizes)
      printSize(data, sizeTuple, 24); 
}
