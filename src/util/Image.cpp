#include <iostream>
#include <vector>

#include <string>
#include <map>
#include <cstdint>


#include "Image.h"

using namespace std;

namespace Image {
  Image::Image(std::string imagePath) : imagePath{imagePath} { } 

  int Image::readImage() {
    return 0;
  }

  bool Image::Image::isValid(std::string file) { return isImage(file); }
  bool Image::Image::isValid(std::filesystem::path filepath) { return isImage(filepath); }

  bool isImage(std::string file) { return File::isFile(file, FileExtensions); }
  bool isImage(std::filesystem::path filepath) { return File::isFile(filepath.string(), FileExtensions); }

  bool imageUnder4MiB (std::filesystem::path imagePath) {
    return under4MiB(imagePath, "Image is too large to fit sounds.");
  }

}
