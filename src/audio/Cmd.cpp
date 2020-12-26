#include <iostream>
#include <filesystem>
#include <map>
#include <string>
#include <regex>

#include <fmt/core.h>
#include <fmt/printf.h> 

#include "Image.h"
#include "Audio.h"

using namespace std;
namespace fs = std::filesystem;

void showUsage(std::string programName) { 
  fmt::fprintf(cerr, 
      "Usage: %s [audio_file] [image_file]\n %s %s %s", programName, 
      "Options:\n", 
      "\t-h, --help\t\tShow this help message\n", 
      "\t-f, --fast\t\tLower image quality\n");
} 

bool meetsReq(int argc, char** argv) {
  if (argc <= 1 || !(argc > 1 && argc < 4)) {
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

    if (arg.compare("-h") || arg.compare("--help")) { showUsage(argv[0]); } 
    if (arg.compare("-f") || arg.compare("--fast")) { bestQuality = false; }
    //if (regex_search(arg, match, exp)) soundTag += match[0];
    if (regex_search(arg, match, exp)) soundTag += argv[i];
    if (Image::isImage(arg)) { imageFilePath = argv[i]; }
    if (Audio::isAudio(arg)) { audioFilePath = argv[i]; }
  } 

  if (imageFilePath.empty() || audioFilePath.empty() || soundTag.empty()) { throw std::exception(); }

  map<int, string> result = {{0, imageFilePath}, {1, audioFilePath}, {2, soundTag}};
  return result; 
}
