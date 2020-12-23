#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <map>
#include <cstdint>

//#include "../file/File.h"
#include "File.h"

namespace Image {
  const static std::map<int, std::string> FileExtensions = {
    {0, ".jpg"},
    {1, ".jpeg"},
    {2, ".gif"},
    {3, ".png"},
    {4, ".webm"},
  };

  struct ImageData {
  };

  class Image {
    private:
      std::string imagePath;

    public:

      Image(std::string imagePath);
      int readImage();

      std::string getImg() {
        return this->imagePath;
      }
  };
  bool isImage(std::string file);
  bool isImage(std::filesystem::path filepath);
  bool imageUnder4MiB (uintmax_t imageFileSize); 
}

#endif
