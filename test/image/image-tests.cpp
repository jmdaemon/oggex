#include "../doctest-main.cpp"

#include <stdlib.h> 
#include <iostream>
#include <string>

#include "Image.h"
#include "FileType.tpp"

using namespace std;
namespace fs = std::filesystem; 

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

  SUBCASE("Running image file checks") {
    std::filesystem::path filepath = "../../inputFile1.png"; 
    ifstream file(filepath, ifstream::in | ifstream::binary);
    CHECK(Image::isImage(filepath));
    CHECK(Image::imageUnder4MiB(std::filesystem::file_size(filepath)));
    REQUIRE(!isCorrupted(filepath, file));
    //REQUIRE(imageNotCorrupted(filepath) == true);
  }

}
