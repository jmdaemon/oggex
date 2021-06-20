#include "ExtractAudio.h"

#include <fmt/format.h>

#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

size_t getOffset(std::filesystem::path filepath, const char* searchTerm) { 
  size_t offset = dataToString(filepath).find(searchTerm);
  if (sizeOf(filepath) == offset) {
    fmt::print(stderr, "Audio offset not found");
    offset = 0;
  }
  return offset; 
}

string findSoundTag(Data& data, string fileData, size_t offset) {
  string tag = fileData.substr(0, offset);
  size_t endTag = tag.rfind("]"); 
  size_t startTag = tag.rfind("[");
  if (endTag == std::string::npos || startTag == std::string::npos) {
    fmt::print("Sound Tag not found.\n");
    return "";
  }
  string unstrippedTag = tag.substr(startTag, endTag); // soundTag = [audio02] => audio02
  string soundTag = (!isEmpty(unstrippedTag, "Sound Tag was not found.")) 
    ?  unstrippedTag.substr(1,  unstrippedTag.length() - 2) : ""; 

  if (data.options.showVerboseEnabled()) { 
    fmt::print("\n================ Sound Tag ================\n");
    fmt::print("Tag: \t\t\t\t: {}\n", unstrippedTag);
    fmt::print("Stripped Tag: \t\t\t: {}\n", soundTag);
  }
  return soundTag; 
} 

std::string formatBytes(Data& data, size_t bytes, bool si = true, unsigned int decimals = 2) {
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
    string result = preciseValue.str() + " \t" + sizes[i];
    preciseValue.clear();
    return result;
}

int extract(Data data) {
  std::filesystem::path image = data.image.getImage();
  size_t embeddedFileSize   = sizeOf(image);
  size_t audioOffset        = getOffset(image);
  size_t audioFileSize      = sizeOf(image, audioOffset);
  if (data.options.showVerboseEnabled()) {
    //fmt::print("\n================ File Sizes ================\n"); 
    //fmt::print("Size of Embedded File \t\t: {} \tbytes\n" , embeddedFileSize);
    //fmt::print("Audio File Size \t\t: {} \tbytes\n\n"     , audioFileSize);
    //fmt::print("\n================ File Offsets ================\n"); 
    //fmt::print("Audio File Offset \t\t: {} \tbytes\n"     , audioOffset); 

    fmt::print("\n================ File Sizes ================\n"); 
    fmt::print("Size of Embedded File \t\t: {}\n" , formatBytes(data, embeddedFileSize, false));
    fmt::print("Audio File Size \t\t: {}\n"     , formatBytes(data, audioFileSize, false));
    fmt::print("\n================ File Offsets ================\n"); 
    fmt::print("Audio File Offset \t\t: {}\n"     , formatBytes(data, audioOffset, false)); 
  }

  string embeddedFileData   = dataToString(image, 0);
  string imageFileData      = readFile(image, 0, audioOffset);
  string audioContent       = dataToString(image, audioOffset);
  string soundTag           = findSoundTag(data, embeddedFileData, audioOffset); 
  if (soundTag.empty()) {
    return -1; 
  } else 
      soundTag += ".ogg";
  if (data.options.showVerboseEnabled()) { fmt::print("Output Audio File \t\t: {}\n\n", soundTag); }
  fmt::print("Extracting audio file as \"{}\"\n", soundTag);

  fs::path audioFileName = (data.options.audioFileEnabled()) ?  fs::path(data.options.getAudioFile()) : soundTag.c_str(); 
  fs::path imageFileName = (data.options.imageFileEnabled()) ?  fs::path(data.options.getImageFile()) : fs::path(image.string() + ".png");
  writeToDisk(audioFileName, audioContent);
  writeToDisk(imageFileName, imageFileData);

  return 0;
}
