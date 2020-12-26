#include "../doctest-main.cpp"

#include "EmbedAudio.h"
#include "File.h"
#include "Image.h"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <map>

using namespace std;
namespace fs = std::filesystem;


TEST_CASE("Audio files can be embedded into image files") {
  SUBCASE("Test toLowerCase()") {
    INFO("Current outPut of toLowerCase(): ");

    REQUIRE(File::toLowerCase("ABC") == "abc");
    REQUIRE(File::toLowerCase(".JPG") == ".jpg");
    CHECK(File::toLowerCase(".JPEG") == ".jpeg");
    CHECK(File::toLowerCase(".PNG") == ".png");
  }


  //SUBCASE("Running image file checks") {
    //std::filesystem::path filepath = "../../inputFile1.png"; 
    //ifstream file(filepath, ifstream::in | ifstream::binary);
    //CHECK(isImage(filepath));
    //CHECK(imageUnder4MiB(std::filesystem::file_size(filepath)));
    //REQUIRE(!isCorrupted(filepath, file));
    ////REQUIRE(imageNotCorrupted(filepath) == true);
  //}

  //SUBCASE("") {
  //}
}
