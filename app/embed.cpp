#include <iostream>
#include <filesystem>
#include <string>
#include <unordered_map>

#include <fmt/core.h>

#include "EmbedAudio.h"
#include "InputParser.h"
#include "Cmd.h"

int main(int argc, char **argv) { 
  InputParser input(argc, argv);
    if(input.argExists("-h") || input.argExists("--help")) {
      showUsage("embed");
      return 0;
    }

    bool bestQuality = true;
    if (input.argExists("-f") || input.argExists("--fast")) {
      bestQuality = false;
    }

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

    for ( const auto& [key, value] : inputs ) {
      if (key.length() > 5) {
        fmt::print ("Key: [{}] {:^13} Value: [{}]\n", key, "", value);
      } else {
        fmt::print ("Key: [{}] {:^16} Value: [{}]\n", key, "", value);
      }
    }

    Audio::AudioData audioData = createAudioData(soundTag, audioFilename);
    Image::ImageData imageData = Image::ImageData(imageFilename);
    Data data = { audioData, imageData, bestQuality };
    embed(data);
    return 0;
}

