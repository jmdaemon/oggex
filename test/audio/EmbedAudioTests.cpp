#include "../doctest-main.cpp"

#include "EmbedAudio.h"
#include <string>
#include <sstream>
#include <iostream>
#include <tuple>
#include <vector>
#include <filesystem>
#include <functional>

using namespace std;
namespace fs = std::filesystem;

TEST_CASE("Audio files can be embedded into image files") {

  SUBCASE("Test toLowerCase()") {
    cout << "Testing toLowerCase()" << endl;
    INFO("Current outPut of toLowerCase(): ");

    REQUIRE(toLowerCase("ABC") == "abc");
    REQUIRE(toLowerCase(".JPG") == ".jpg");
    CHECK(toLowerCase(".JPEG") == ".jpeg");
    CHECK(toLowerCase(".PNG") == ".png");
  }

  SUBCASE("Testing parseOptions()") {
    string inputString = "Test_parseOptions()";
    std::vector<char> writable(inputString.begin(), inputString.end());
    writable.push_back('\0');
    char* inputptr = &writable[0];
    char** inputpptr = &inputptr;

    CHECK_THROWS_AS(parseOptions(0, inputpptr), std::exception);
    string input = "image.png audio.ogg";
    std::vector<char> inputVector(input.begin(), input.end());
    inputVector.push_back('\0');
    char* inputPtr = &inputVector[0];
    char** inputPptr = &inputPtr;

    //tuple<fs::path, fs::path> checkResult = tuple<fs::path, fs::path>{"image.png", "audio.ogg"};
    //tuple<fs::path, fs::path> result = parseOptions(2, {"image.png", "audio.ogg"});
    //tuple<fs::path, fs::path> result = parseOptions(2, inputPptr);
    //tuple<fs::path, fs::path> result = parseOptions(2, inputPptr);
    //tuple<string, string> resultCast = make_tuple(get<0>(result), get<1>(result));
    //tuple<string, string> result = parseOptions(2, inputPptr);
    //auto result = parseOptions(2, inputPptr);

    //auto checkResult = make_tuple("image.png", "audio.ogg");
    //for (auto const& [key, val] : symbolTable) {
        //std::cout << key        // string (key)
                  //<< ':'  
                  //<< val        // string's value
                  //<< std::endl; 
    //}

    //auto result = make_tuple("image.png", "audio.ogg");
    //for (int i = 0; i < 2; i++) { 
      ////string file = (get<i>(result)).string();
      ////string file = get<i>(resultCast);
      ////string file = std::get<i>(result);
      ////string checkFile = std::get<i>(checkResult);
      ////string file = get<i>(result);
      ////string checkFile = std::get<i>(checkResult);
      //string file = get<0>(result);
      //string checkFile = std::get<0>(checkResult);
      ////string checkFile = (get<i>(checkResult)).string();
      //CHECK(file == checkFile);
    //}
  } 
}
