#include "Cmd.h"

using namespace std;
namespace fs = std::filesystem;

void showUsage(std::string programName) { 
  fmt::print(stderr, 
      "Usage: {} [audio_file] [sound_tag] [image_file]\n{}\n{}\n{}\n{}\n{}\n{}\n \n\n", programName, 
      "Options:", 
      "\t-h, --help\t\tShow this help message",
      "\t-f, --fast\t\tLower image quality",
      "\t-a, \t\tThe file path to the audio file",
      "\t-i, \t\tThe file path to the image file",
      "\t-t, \t\tThe caption or tag for the audio file"
      );
} 

bool meetsReq(int argc, char** argv) {
  if (argc <= 1) {
    fmt::print("# of Arguments passed: \t{}\n", argc);
    showUsage(argv[0]);
    throw std::exception();
  } 
  return true;
}

map<int, string> parseOptions(int argc, char** argv, bool bestQuality = true) {
  if (!meetsReq(argc, argv)) { throw std::exception(); }

  fs::path imageFilePath;
  fs::path audioFilePath;

  regex exp("(\\[\\w+\\])");
  string soundTag = "";
  smatch match;

  for (int i = 0; i < argc; i++) {
    string arg = string(argv[i]);

    if (arg == "-h" || arg == "--help") { 
      showUsage(argv[0]); 
      map<int, string> quitEarly = {{0, ""}};
      fmt::print("Exiting program...\n");
      return quitEarly;
    } 
    if (arg.compare("-f") || arg.compare("--fast")) { bestQuality = false; }
    if (regex_search(arg, match, exp)) 
      soundTag = arg;
    //if (Image::isImage(arg)) { imageFilePath = arg; }
  } 
  imageFilePath = "";
  audioFilePath = "";
  if (imageFilePath.empty() || audioFilePath.empty() || soundTag.empty()) { throw std::exception(); }
  //if (!under4MiB(imageFilePath) || !fileExists(imageFilePath) || !fileExists(audioFilePath)) { return -1; } 

  map<int, string> result = {{0, imageFilePath}, {1, audioFilePath}, {2, soundTag}};
  //Audio::AudioData audioData = createAudioData(soundTag, audioFilePath);
  return result; 
}

bool isEmpty(string arg, string errorMsg) {
  if (arg.empty()) { 
    showUsage("embed");
    fmt::print(stderr, "{}\n", errorMsg);
    return true;
  }
  else
    return false;
}
