#include <iostream>
#include <string>
#include <filesystem>

#include "ExtractAudio.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv) { 
  fs::path filepath = "";
  if (!string(argv[1]).empty())
    filepath = argv[1];
  extract(filepath);
  return 0;
}
