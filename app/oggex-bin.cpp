#include "oggex.h"
#include "InputParser.h"
#include "cli.h"

//extern "C" struct arguments set_default_args() {
  //return set_default_args();
//}

int main(int argc, char **argv) {

  struct arguments arguments = set_default_args();
  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  //int verbose = arguments.verbose;
  char* command = arguments.args[0];
  //int scale = arguments.scale;

  Sound sound = arguments.sound;
  Settings settings = { 10, false };
  Media media = {sound, settings, arguments};

  // Error checking
  if (!file_exists(sound.src))
    fmt::print("{}", "You must provide a valid .ogg audio file.");

  if (!file_exists(sound.image))
    fmt::print("{}", "You must provide a valid image file. Supported image formats are: PNG, JPG, JPEG and GIF.");

  if (sizeof(sound.tag) == 0)
    fmt::print("{}", "You cannot have an empty sound tag");
  
  // Parsing
  if (strcmp(command, "embed") == 0) {
    //Sound sound = {(char *)audioFilename.c_str(), (char*) imageFilename.c_str(), (char *) "", (char *) "", (char *) soundTag.c_str()};
    embed(media);
  } else if (strcmp(command, "extract") == 0) {
    extract(media);
  }
  //InputParser input(argc, argv);
  //if (input.argExists("-h") || input.argExists("--help")) {
    //showUsage("oggex");
    //return 0;
  //} 

  //Options options; // Enable options
  //for ( const auto& [option, flag] : options.getOptions() ) {           // Get the hashmap of toggled options 
    //auto [ shortFlag, longFlag, enabled ] = flag;
    //if (!longFlag.empty()) {                                            // If LongFlag is not empty 
      //options.enable(option, input.toggleOption(shortFlag, longFlag));  // Use both flags, and enable the option 
    //} else {
      //options.enable(option, input.toggleOption(shortFlag));            // Use the ShortFlag to enable the option
    //}
  //}

  //std::unordered_map<std::string, std::string> Errors = {
    //{"InvalidAudioFile", "You must provide a valid .ogg audio file."},
    //{"InvalidImageFile", "You must provide a valid image file. Supported image formats are: PNG, JPG, JPEG and GIF."},
    //{"EmptySoundTag", "You must provide a sound tag."}
  //};

  //if (input.toggleOption("-m", "embed")) { 
    //const std::string &audioFilename = input.getArg("-a");
    //if (isEmpty(audioFilename, Errors["InvalidAudioFile"]) || !file_exists(audioFilename.c_str())) { return -1; }
    
    //const std::string &imageFilename = input.getArg("-i");
    //if (isEmpty(imageFilename, Errors["InvalidImageFile"]) || !file_exists(imageFilename.c_str())) { return -1; }

    //const std::string &soundTag = input.getArg("-t");
    //if (isEmpty(soundTag, Errors["EmptySoundTag"])) { return -1; } 

    //options.setOutput(input.getArg("-d"));

    //std::unordered_map<std::string, std::string> inputs = {
      //{"Audio", audioFilename},
      //{"Image", imageFilename},
      //{"SoundTag", soundTag}
    //};
    //Sound sound = {(char *)audioFilename.c_str(), (char*) imageFilename.c_str(), (char *) "", (char *) "", (char *) soundTag.c_str()};
    //Settings settings = { 10, false };
    //Media media = {sound, settings};

    //if (options.showVerboseEnabled()) {
      //fmt::print("\n================ Inputs ================\n");
      //for ( const auto& [key, value] : inputs ) { 
        //printSize("[" + key + "]", "[" + value + "]", 16);
      //}
      //fmt::print("\n");
    //} 
    //embed(media); 
  //} else if (input.toggleOption("-x", "extract")) {
    //const std::string &imageFilename = input.getArg("-i");
    //if (isEmpty(imageFilename, Errors["InvalidImageFile"]) || !file_exists(imageFilename.c_str())) { return -1; } 

    //options.setAudio(input.getArg("-ad"));
    //options.setImage(input.getArg("-id"));

    //Sound sound = {(char *)"", (char*) imageFilename.c_str(), (char *) "", (char *) ""};
    //Settings settings = { 10, false };
    //Media media = {sound, settings};

    //extract(media);
  //} else 
      //showUsage("oggex");
  return 0;
}
