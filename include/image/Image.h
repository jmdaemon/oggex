#ifndef IMAGE_H
#define IMAGE_H

#include <string>

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

#endif
