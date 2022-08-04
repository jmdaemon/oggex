#pragma once
#ifndef IMAGE_H
#define IMAGE_H

//#include "File.h"

#include <string>
#include <map>
#include <filesystem>

namespace Image {
  class ImageData {
    private: 
      std::map<int, std::string> FileExtensions = { 
        { 0, ".jpg"},
        { 1, ".jpeg"},
        { 2, ".gif"},
        { 3, ".png"},
        { 4, ".webm"},
      };

      std::string imagePath;

    public:
      ImageData(std::string imagePath);
      ImageData(): imagePath{""} {}

      std::filesystem::path createOutputFilename();
      std::string getImage() { return this->imagePath; }
      void setImage(std::string imagePath) { this->imagePath = imagePath; }
  };

  bool imageUnder4MiB (std::filesystem::path imagePath); 
}

#endif
