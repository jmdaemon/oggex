#include <iostream>
#include <filesystem>


#include "EmbedAudio.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv) {

  embed(argc, argv);
  return 0;
}

