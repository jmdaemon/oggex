#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <map>

namespace Image {
  const static std::map<int, std::string> FileExtensions = {
    {0, ".jpg"},
    {1, ".jpeg"},
    {2, ".gif"},
    {3, ".png"},
    {4, ".webm"},
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
}

#endif
