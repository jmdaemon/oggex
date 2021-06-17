#include <iostream>
#include <filesystem>
#include <string>
#include <unordered_map>

#include <fmt/core.h>

#include "EmbedAudio.h" 
#include "ExtractAudio.h"
#include "InputParser.h"
#include "Data.h"
#include "Cmd.h"

int main(int argc, char **argv) { 
  InputParser input(argc, argv);
  if (input.argExists("-h") || input.argExists("--help")) {
    showUsage("oggex");
    return 0;
  } 

  bool enableMonoAudio    = input.toggleOption("-f", "--fast");
  bool ignoreSizeLimit    = input.toggleOption("-ig", "--ignore-limit");
  bool showDebugInfo      = input.toggleOption("-v", "--verbose");
  bool setOutputFilename  = input.toggleOption("-d", "--dest");
  bool setAudioFilename   = input.toggleOption("-ad");
  bool setImageFilename   = input.toggleOption("-id");

  std::unordered_map<std::string, std::string> Errors = {
    {"InvalidAudioFile", "You must provide a valid .ogg audio file."},
    {"InvalidImageFile", "You must provide a valid image file. Supported image formats are: PNG, JPG, JPEG and GIF."},
    {"EmptySoundTag", "You must provide a sound tag."}
  };

  if (input.toggleOption("-m", "embed")) { 
    const std::string &audioFilename = input.getArg("-a");
    if (isEmpty(audioFilename, Errors["InvalidAudioFile"]) || !fileExists(audioFilename)) { return -1; }
    
    const std::string &imageFilename = input.getArg("-i");
    if (isEmpty(imageFilename, Errors["InvalidImageFile"]) || !fileExists(imageFilename)) { return -1; }

    const std::string &soundTag = input.getArg("-t");
    if (isEmpty(soundTag, Errors["EmptySoundTag"])) { return -1; }

    std::unordered_map<std::string, std::string> inputs = {
      {"Audio", audioFilename},
      {"Image", imageFilename},
      {"SoundTag", soundTag}
    };
    Data data = createEmbedData(createAudioData(soundTag, audioFilename), Image::ImageData(imageFilename), 
        enableMonoAudio, ignoreSizeLimit, showDebugInfo, setOutputFilename);

    if (data.showDebugInfo) {
      fmt::print("\n================ Inputs ================\n");
      for ( const auto& [key, value] : inputs ) {
        if (key.length() > 5) {
          fmt::print ("Key: [{}] {:^13} Value: [{}]\n", key, "", value);
        } else {
          fmt::print ("Key: [{}] {:^16} Value: [{}]\n", key, "", value);
        }
      }
      fmt::print("\n");
    } 
    embed(data); 
  } else if (input.toggleOption("-x", "extract")) {
    const std::string &imageFilename = input.getArg("-i");
    if (isEmpty(imageFilename, Errors["InvalidImageFile"]) || !fileExists(imageFilename)) { return -1; }
    Data data = createExtractData(Image::ImageData(imageFilename), showDebugInfo, setAudioFilename, setImageFilename);
    extract(data);
  } else 
      showUsage("oggex");
  return 0;
}
