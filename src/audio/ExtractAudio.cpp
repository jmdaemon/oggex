#include "ExtractAudio.h"

#include <tuple>
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
    //fmt::print("{:<24} {:>10} : {}\n", "Tag", "", unstrippedTag);
    //fmt::print("{:<24} {:>10} : {}\n", "Stripped Tag", "", soundTag);
    fmt::print("{:<24} : {:<8}\n", "Tag", unstrippedTag);
    fmt::print("{:<24} : {:<8}\n", "Stripped Tag", soundTag);
    //fmt::print("Tag: \t\t\t\t: {}\n", unstrippedTag);
    //fmt::print("Stripped Tag: \t\t\t: {}\n", soundTag);
  }
  return soundTag; 
} 

int extract(Data data) {
  std::filesystem::path image = data.image.getImage();
  size_t embeddedFileSize   = sizeOf(image);
  size_t audioOffset        = getOffset(image);
  size_t audioFileSize      = sizeOf(image, audioOffset);
  if (data.options.showVerboseEnabled()) { 
    auto EFS = formatBytes(data, embeddedFileSize);
    auto AFS = formatBytes(data, audioFileSize);
    auto AO  = formatBytes(data, audioOffset);

    fmt::print("\n================ File Sizes ================\n"); 
    //fmt::print("Size of Embedded File   : {:<8} {}\n" , std::get<0>(EFS), std::get<1>(EFS));
    //fmt::print("Audio File Size         : {:<8} {}\n" , std::get<0>(AFS), std::get<1>(AFS));
    //fmt::print("Audio File Offset       : {:<8} {}\n" , std::get<0>(AO) , std::get<1>(AO)); 
    //fmt::print("\n================ File Offsets ================\n"); 
    //fmt::print("{:<24} : {:<8} {}\n" , "Size of Embedded File", "", std::get<0>(EFS), std::get<1>(EFS));
    //fmt::print("{:<24} : {:<8} {}\n" , "Audio File Size", "", std::get<0>(AFS), std::get<1>(AFS));
    //fmt::print("{:<24} : {:<8} {}\n" , "Audio File Offset", "", std::get<0>(AO) , std::get<1>(AO)); 
    fmt::print("{:<24} : {:<8} {}\n" , "Size of Embedded File", std::get<0>(EFS), std::get<1>(EFS));
    fmt::print("{:<24} : {:<8} {}\n" , "Audio File Size", std::get<0>(AFS), std::get<1>(AFS));
    fmt::print("{:<24} : {:<8} {}\n" , "Audio File Offset", std::get<0>(AO), std::get<1>(AO)); 
  }

  string embeddedFileData   = dataToString(image, 0);
  string imageFileData      = readFile(image, 0, audioOffset);
  string audioContent       = dataToString(image, audioOffset);
  string soundTag           = findSoundTag(data, embeddedFileData, audioOffset); 
  if (soundTag.empty()) {
    return -1; 
  } else 
      soundTag += ".ogg";
  //if (data.options.showVerboseEnabled()) { fmt::print("Output Audio File \t\t: {}\n\n", soundTag); }
  if (data.options.showVerboseEnabled()) { 
    //fmt::print("Output Audio File \t\t: {}\n\n", soundTag); 
    fmt::print("{:<24} : {:<8}\n\n", "Output Audio File", soundTag); 
  }
  fmt::print("Extracting audio file as \"{}\"\n", soundTag);

  fs::path audioFileName = (data.options.audioFileEnabled()) ?  fs::path(data.options.getAudioFile()) : soundTag.c_str(); 
  fs::path imageFileName = (data.options.imageFileEnabled()) ?  fs::path(data.options.getImageFile()) : fs::path(image.string() + ".png");
  writeToDisk(audioFileName, audioContent);
  writeToDisk(imageFileName, imageFileData);

  return 0;
}
