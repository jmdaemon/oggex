#include "../doctest-main.cpp"

#include "EmbedAudio.h"
#include <string>
#include <sstream>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

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
  } 
}
