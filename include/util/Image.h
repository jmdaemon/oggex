#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <map>

#include "File.h"

namespace Image {
  const static std::map<int, std::string> FileExtensions = {
    {0, ".jpg"},
    {1, ".jpeg"},
    {2, ".gif"},
    {3, ".png"},
    {4, ".webm"},
  };

  class ImageData : public File::File {
    private:
      std::string imagePath;

    public:
      ImageData(std::string imagePath);
      ImageData(): imagePath{""} {}

      virtual bool isValid(std::string file);
      virtual bool isValid(std::filesystem::path filepath);

      std::filesystem::path createOutputFilename();

      std::string getImage() { return this->imagePath; }
      void setImage(std::string imagePath) { this->imagePath = imagePath; }
  };
  bool isImage(std::string file);
  bool isImage(std::filesystem::path filepath);
  bool imageUnder4MiB (std::filesystem::path imagePath); 
}

#endif
