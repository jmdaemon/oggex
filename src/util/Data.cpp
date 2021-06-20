#include "Data.h"

#include <iosfwd>
#include <tuple>

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
