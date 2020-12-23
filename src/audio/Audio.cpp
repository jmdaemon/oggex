#include <filesystem>
#include <map>
#include <string>

#include "Audio.h"

namespace Audio {
  bool isAudio(std::string file) { return File::isFile(file, FileExtensions); }
  bool isAudio(std::filesystem::path filepath) { return File::isFile(filepath.string(), FileExtensions); }

}
