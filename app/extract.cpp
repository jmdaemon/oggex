#include <iostream>
#include <string>
#include <filesystem>

#include "ExtractAudio.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv) {
  //string path;
  //if (argc > 0 && argc < 2) 
    //std::string path = argv[1];

  //fs::path filepath = argv[0];
  //fs::path filepath = path;
  fs::path filepath = argv[1];
  extract(filepath);
  return 0;
}
