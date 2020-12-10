#define CATCH_CONFIG_MAIN
//#include "doctest/doctest.h"

#include <iostream>
#include <string>
#include <stdlib.h>

//#include "include/image.hpp"
//#include "Image/image.hpp"
//#include "Image.hpp"
#include "Image.hpp"
//#include "doctest.h"
#include "doctest/doctest.h"

bool readImgFromPath() {
  std::string filepath = ("../../resources/12727a5f30b1429a1fd35113fd2550d8.png");
  Image testImage = Image(filepath);
  if (testImage.readImage()) {
    //return "Successfully read file";
    return true;
  } else
    //return "Unable to read file";
    return false;
}

TEST_CASE("Testing Image class") {
  //CHECK(readImage() == "Successfully read file");
  CHECK(readImgFromPath() == true);
}
