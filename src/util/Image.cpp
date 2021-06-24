#include "Image.h"

using namespace std;

namespace Image {
  ImageData::ImageData(std::string imagePath) : imagePath{imagePath} { } 

  std::filesystem::path Image::ImageData::createOutputFilename() { 
    std::filesystem::path imageFilePath = this->imagePath;
    return (string(imageFilePath.stem()) + "-embed" + string(imageFilePath.extension()));
  }

  bool imageUnder4MiB (std::filesystem::path imagePath) {
    return under4MiB(imagePath, "Image is too large to fit sounds.");
  }

}
