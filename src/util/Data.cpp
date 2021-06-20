#include "Data.h"

Data createEmbedData(Audio::AudioData audio, Image::ImageData image, Options options) { 
  return Data{ .audio = audio, .image = image, .options = options};
}

Data createExtractData(Image::ImageData image, Options options) {
  return Data{ .image = image, .options = options};
}

std::string formatBytes(Data& data, size_t bytes, bool si, unsigned int decimals) {
    int unit = (si) ? 1000 : 1024; 
    const unsigned int dm = (decimals < 0) ? 0 : decimals;
    std::map<int, std::string> sizes;
    if (si) {
      sizes = {
        { 0, "Bytes"}, 
        { 1, "KB"}, 
        { 2, "MB"}, 
        { 3, "GB"}, 
        { 4, "TB"},
        { 5, "PB"}, 
        { 6, "EB"}, 
        { 7, "ZB"}, 
        { 8, "YB"}
        };
    } else { 
      sizes = { 
        { 0, "Bytes"}, 
        { 1, "KiB"}, 
        { 2, "MiB"}, 
        { 3, "GiB"}, 
        { 4, "TiB"},
        { 5, "PiB"}, 
        { 6, "EiB"}, 
        { 7, "ZiB"}, 
        { 8, "YiB"} 
      }; 
    }

    if (!data.options.isReadableEnabled()) { 
      std::stringstream ss; 
      ss << bytes << " \t" << sizes[0]; 
      std::string result = ss.str();
      ss.clear();
      return result;
    } 

    const double i = floor(std::log(bytes) / std::log(unit)); 
    double res = (bytes / std::pow(unit, i)); 

    std::stringstream preciseValue; 
    preciseValue.precision(dm); 
    preciseValue << res;
    std::string result = preciseValue.str() + " \t" + sizes[i];
    preciseValue.clear();
    return result;
}

