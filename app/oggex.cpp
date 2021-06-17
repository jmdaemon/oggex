#include <iostream>
#include <filesystem>
#include <string>
#include <unordered_map>

#include <fmt/core.h>

#include "EmbedAudio.h" 
#include "ExtractAudio.h"
#include "InputParser.h"
#include "Cmd.h"
#include "Options.h"

int main(int argc, char **argv) { 
  InputParser input(argc, argv);
  if (input.argExists("-h") || input.argExists("--help")) {
    showUsage("oggex");
    return 0;
  } 

  Options options;

  options.enableMono      (input.toggleOption("-f", "--fast"));
  options.ignoreLimit     (input.toggleOption("-ig", "--ignore-limit"));
  options.showVerbose     (input.toggleOption("-v", "--verbose"));
  options.setOutputFile   (input.toggleOption("-d", "--dest"));
  options.setAudioFile    (input.toggleOption("-ad"));
  options.setImageFile    (input.toggleOption("-id"));

  const std::string &outputFile = input.getArg("-d");
  const std::string &audioFile  = input.getArg("-ad");
  const std::string &imageFile  = input.getArg("-id");

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
    //Data data = createEmbedData(createAudioData(soundTag, audioFilename), Image::ImageData(imageFilename), 
        //enableMonoAudio, ignoreSizeLimit, showDebugInfo, setOutputFilename);
    Data data = Data{ createAudioData(soundTag, audioFilename), Image::ImageData(imageFilename), options };

    if (options.showVerboseEnabled()) {
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
    //Data data = createExtractData(Image::ImageData(imageFilename), showDebugInfo, setAudioFilename, setImageFilename);
    Data data = Data{ createAudioData("", ""), Image::ImageData(imageFilename), options };
    extract(data);
  } else 
      showUsage("oggex");
  return 0;
}
