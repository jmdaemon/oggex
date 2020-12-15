#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

#include "image.hpp"

using namespace std;

Image::Image(std::string imagePath) : imagePath{imagePath} { 
//Image::Image(std::string imagePath) { 
  //setImg(imagePath); 
  //this->imagePath{imagePath};
} 

int Image::readImage() {
  return 0;
}
