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
  string tag = fileData.substr(offset - 100, offset);
  //regex exp("(\\[\\w+\\])(\?!OggS)");
  regex exp("(\\[\\w+\\])");

  string unstrippedTag = "";
  string soundTag = "";
  smatch match;
  if (regex_search(tag, match, exp)) { 
    unstrippedTag = match[0]; // soundTag = [audio02] => audio02

    soundTag = (!isEmpty(unstrippedTag, "Sound Tag was not found.")) 
      ?  unstrippedTag.substr(1,  unstrippedTag.length() - 2) : ""; 

    if (data.options.showVerboseEnabled()) { 
      fmt::print("\n================ Sound Tag ================\n");
      fmt::print("Tag: \t\t\t\t: {}\n", unstrippedTag);
      fmt::print("Stripped Tag: \t\t\t: {}\n", soundTag);
    }
  }
  return soundTag; 
} 
void rename(Data& data, std::string outputFile, std::string from, std::string to) {
  if (data.options.isEnabled(outputFile)) {
    std::filesystem::rename(std::filesystem::path(from), std::filesystem::path(to));
    data.options.setFileName(outputFile, std::filesystem::path(to));
  }
}

int extract(Data data) {
  std::filesystem::path image = data.image.getImage();
  size_t embeddedFileSize   = sizeOf(image);
  size_t audioOffset        = getOffset(image);
  size_t audioFileSize      = sizeOf(image, audioOffset);
  if (data.options.showVerboseEnabled()) {
    fmt::print("\n================ File Sizes ================\n"); 
    fmt::print("Size of Embedded File \t\t: {} \tbytes\n" , embeddedFileSize);
    fmt::print("Audio File Size \t\t: {} \tbytes\n\n"     , audioFileSize);
    fmt::print("\n================ File Offsets ================\n"); 
    fmt::print("Audio File Offset \t\t: {} \tbytes\n"     , audioOffset); 
  }

  string embeddedFileData   = dataToString(image, 0);
  string imageFileData      = readFile(image, 0, audioOffset);
  string audioContent       = dataToString(image, audioOffset);
  string soundTag           = findSoundTag(data, embeddedFileData, audioOffset); 
  if (soundTag.empty()) { 
    return -1; 
  } else { 
    soundTag += ".ogg";
  }
  if (data.options.showVerboseEnabled()) { fmt::print("Output Audio File \t\t: {}\n\n", soundTag); }
  fmt::print("Extracting audio file as \"{}\"\n", soundTag);

  writeToDisk(soundTag.c_str(), audioContent);
  writeToDisk(fs::path(image.string() + ".png"), imageFileData);

  rename(data, "AudioFile", soundTag, data.options.getAudioFile());
  rename(data, "ImageFile", (image.string() + ".png"), data.options.getImageFile()); 

  return 0;
}
