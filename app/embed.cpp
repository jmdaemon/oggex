#include <iostream>
#include <filesystem>
#include <string>
#include <unordered_map>

#include <fmt/core.h>

#include "EmbedAudio.h" 
#include "ExtractAudio.h"
#include "InputParser.h"
#include "Cmd.h"

int main(int argc, char **argv) { 
  InputParser input(argc, argv);

    if (input.argExists("-h") || input.argExists("--help")) {
      showUsage("oggex");
      return 0;
    }

    bool enableMonoAudio  = input.toggleOption("-f", "--fast");
    bool ignoreSizeLimit  = input.toggleOption("-ig", "--ignore-limit");
    bool showDebugInfo    = input.toggleOption("-v", "--verbose");

    const std::string &audioFilename = input.getArg("-a");
    if (isEmpty(audioFilename, "You must provide a valid .ogg audio file.")) { return -1; }
    
    const std::string &imageFilename = input.getArg("-i");
    if (isEmpty(imageFilename, "You must provide a valid image file. Supported image formats are: PNG, JPG, JPEG and GIF.")) { return -1; }

    const std::string &soundTag = input.getArg("-t");
    if (isEmpty(soundTag, "You must provide a sound tag.")) { return -1; }

    // Check the following:
    // Audio and Image files exist on system
    // That the Audio, Image and SoundTag combined, are all less than MAX_SIZE = 4 MiB
    if (!fileExists(audioFilename)) { return -1; }
    if (!fileExists(imageFilename)) { return -1; }

    std::unordered_map<std::string, std::string> inputs = {
      {"Audio", audioFilename},
      {"Image", imageFilename},
      {"SoundTag", soundTag}
    };

    Audio::AudioData audioData = createAudioData(soundTag, audioFilename);
    Image::ImageData imageData = Image::ImageData(imageFilename);
    Data data = { audioData, imageData, enableMonoAudio, ignoreSizeLimit, showDebugInfo };

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
    return 0;
}

