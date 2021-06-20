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

  Options options; // Enable options
  for ( const auto& [option, flag] : options.getOptions() ) {           // Get the hashmap of toggled options 
    auto [ shortFlag, longFlag, enabled ] = flag;
    if (!longFlag.empty()) {                                            // If LongFlag is not empty 
      options.enable(option, input.toggleOption(shortFlag, longFlag));  // Use both flags, and enable the option 
    } else {
      options.enable(option, input.toggleOption(shortFlag));            // Use the ShortFlag to enable the option
    }
  }

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

    options.setOutput(input.getArg("-d"));

    std::unordered_map<std::string, std::string> inputs = {
      {"Audio", audioFilename},
      {"Image", imageFilename},
      {"SoundTag", soundTag}
    };
    Data data = createEmbedData( createAudioData(soundTag, audioFilename), Image::ImageData(imageFilename), options );

    if (options.showVerboseEnabled()) {
      fmt::print("\n================ Inputs ================\n");
      //fmt::print("[{}]", );
      for ( const auto& [key, value] : inputs ) { 
        //std::string input = fmt::format("Input: [{}]", key);
        //std::string val = fmt::format("Value: [{}]", value);
        //fmt::print ("Key: [{}]{:<12} {:>8} Value: [{}]\n", key, " ","", value);
        //fmt::print ("{} {:>28}\n", input, val);
        //std::string input = "Key: [" + key + "]";
        //std::string val   = "Value: [" + value + "]";
        std::string Key = "[" + key + "]";
        std::string Val = "[" + value + "]";
        //fmt::print("[{:>12}] : {:<16} [{}]\n", key, " ", value);
        fmt::print("{:<16} : {:<8}\n", Key, Val);

        ////fmt::print ("{Key: [{}] {:<28}} Value: [{}]\n", key, " ", value);
        //fmt::print ("{} {: ^16} \n", input, val);
        //if (key.length() > 5) {
          //fmt::print ("Key: [{}] {:^13} Value: [{}]\n", key, "", value);
        //} else {
          //fmt::print ("Key: [{}] {:^16} Value: [{}]\n", key, "", value);
        //}
      }
      fmt::print("\n");
    } 
    embed(data); 
  } else if (input.toggleOption("-x", "extract")) {
    const std::string &imageFilename = input.getArg("-i");
    if (isEmpty(imageFilename, Errors["InvalidImageFile"]) || !fileExists(imageFilename)) { return -1; } 

    options.setAudio(input.getArg("-ad"));
    options.setImage(input.getArg("-id"));

    Data data = createExtractData( Image::ImageData(imageFilename), options );
    extract(data);
  } else 
      showUsage("oggex");
  return 0;
}
