#include <iostream>
#include <filesystem>

#include "ExtractAudio.h"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
  fs::path filepath = argv[0];
  extract(filepath);
  return 0;
}
