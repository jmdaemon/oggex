#include <filesystem>
#include <iostream>
#include <map>
#include <regex>
#include <string>

#include <fmt/core.h>
#include <fmt/printf.h> 

#include "Audio.h"
#include "Image.h"

using namespace std;
namespace fs = std::filesystem;

void showUsage(std::string programName) { 
  fmt::fprintf(cerr, 
      "Usage: %s [audio_file] [sound_tag] [image_file]\n %s %s %s", programName, 
      "Options:\n", 
      "\t-h, --help\t\tShow this help message\n", 
      "\t-f, --fast\t\tLower image quality\n");
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
    if (Image::isImage(arg)) { imageFilePath = arg; }
    if (Audio::isAudio(arg)) { audioFilePath = arg; } 
  } 

  if (imageFilePath.empty() || audioFilePath.empty() || soundTag.empty()) { throw std::exception(); }

  map<int, string> result = {{0, imageFilePath}, {1, audioFilePath}, {2, soundTag}};
  return result; 
}
