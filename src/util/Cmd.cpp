#include "Cmd.h"

void showUsage(std::string programName) { 
  fmt::print(stderr, 
      "Usage: {} [embed/extract] -a [audio] -t [soundtag] -i [image]\nOptions:\n    Embedding:\n{}\n{}\n{}\n{}\n{}\n{}\n{}\n{}\n    Encoding:\n \n\n", programName, 
      "\tembed, \t-m\t\tEmbed an audio file",
      "\t-h,  \t--help\t\tShow this help message",
      "\t-f,  \t--fast\t\tEnable Mono Audio Channel encoding",
      "\t-ig, \t--ignore-limit\tAllows you to encode files greater than 4 MiB",
      "\t-v,  \t--verbose\tDisplay program output and debugging information",
      "\t-a,  \t\t\tThe file path to the audio file",
      "\t-i,  \t\t\tThe file path to the image file",
      "\t-t,  \t\t\tThe caption or tag for the audio file"
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

bool isEmpty(std::string arg, std::string errorMsg) {
  if (arg.empty()) { 
    showUsage("embed");
    fmt::print(stderr, "{}\n", errorMsg);
    return true;
  }
  else
    return false;
} 
