#include "../doctest-main.cpp"

#include "Image.h"

#include <stdlib.h> 
#include <iostream>
#include <string>

std::string readImage() {
  std::string filepath = ("../../resources/12727a5f30b1429a1fd35113fd2550d8.png");
  Image::Image testImage = Image::Image(filepath);
  if (testImage.readImage() == 0) {
    return "Successfully read file";
  } else
    return "Unable to read file";
}

TEST_CASE("Testing Image class") { 
  CHECK(readImage() == "Successfully read file");
}
