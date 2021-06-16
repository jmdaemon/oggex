#include "Image.h"

using namespace std;

namespace Image {
  ImageData::ImageData(std::string imagePath) : imagePath{imagePath} { } 

  bool Image::ImageData::isValid(std::string file) { return isImage(file); }
  bool Image::ImageData::isValid(std::filesystem::path filepath) { return isImage(filepath); }

  bool isImage(std::string file) { return File::isFile(file, FileExtensions); }
  bool isImage(std::filesystem::path filepath) { return File::isFile(filepath.string(), FileExtensions); }

  bool imageUnder4MiB (std::filesystem::path imagePath) {
    return under4MiB(imagePath, "Image is too large to fit sounds.");
  }

}
