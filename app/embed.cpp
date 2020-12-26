#include <iostream>
#include <filesystem>


#include "EmbedAudio.h"
//#include "File.h"
//#include "Image.h"
//#include "Audio.h" 
#include "Cmd.h"

using namespace std;
namespace fs = std::filesystem;

static bool bestQuality;
int main(int argc, char** argv) {
  map<int, string> mediaFiles;
  try {
    mediaFiles = parseOptions(argc, argv, bestQuality);
  } catch (const std::exception&) {
    return -1;
  }

  fs::path audioFilePath = mediaFiles[0];
  fs::path imageFilePath = mediaFiles[1];

  embed(audioFilePath, imageFilePath, bestQuality);
  //embed(argc, argv);
  return 0;
}

