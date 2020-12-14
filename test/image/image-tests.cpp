#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

#include "image.hpp"

#include <stdlib.h> 
#include <iostream>
#include <string>

std::string readImage() {
  std::string filepath = ("../../resources/12727a5f30b1429a1fd35113fd2550d8.png");
  Image testImage = Image(filepath);
  if (testImage.readImage() == 0) {
    return "Successfully read file";
  } else
    return "Unable to read file";
}

int main(int argc, char** argv) {
  return 0;
}

TEST_CASE("Testing Image class") { 
  CHECK(readImage() == "Successfully read file");
}