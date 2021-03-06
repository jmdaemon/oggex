#include "ExtractAudio.h"

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
    printSize("Tag", unstrippedTag);
    printSize("Stripped Tag", soundTag);
  }
  return soundTag; 
} 

int extract(Data data) {
  std::filesystem::path image = data.image.getImage();
  size_t embeddedFileSize   = sizeOf(image);
  size_t audioOffset        = getOffset(image);
  size_t audioFileSize      = sizeOf(image, audioOffset);

  if (data.options.showVerboseEnabled()) { printExtractSizes(data, embeddedFileSize, audioFileSize, audioOffset); }

  string embeddedFileData   = dataToString(image, 0);
  string imageFileData      = readFile(image, 0, audioOffset);
  string audioContent       = dataToString(image, audioOffset);
  string soundTag           = findSoundTag(data, embeddedFileData, audioOffset); 
  if (soundTag.empty()) {
    return -1; 
  } else 
      soundTag += ".ogg";
  if (data.options.showVerboseEnabled()) { printSize("Output Audio File", soundTag); }
  fmt::print("Extracting audio file as \"{}\"\n", soundTag);

  fs::path audioFileName = (data.options.audioFileEnabled()) ?  fs::path(data.options.getAudioFile()) : soundTag.c_str(); 
  fs::path imageFileName = (data.options.imageFileEnabled()) ?  fs::path(data.options.getImageFile()) : fs::path(image.string() + ".png");
  writeToDisk(audioFileName, audioContent);
  writeToDisk(imageFileName, imageFileData);

  return 0;
}
