#include "../doctest-main.cpp"

#include "EmbedAudio.h"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <map>

using namespace std;
namespace fs = std::filesystem;

template <typename Map>

bool key_compare (Map const &lhs, Map const &rhs) {
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(), rhs.begin(), 
                      [] (auto a, auto b) { return a.first == b.first; });
}
char** createArgvInput(string arg) {
    string input = arg;
    std::vector<char> inputVector(input.begin(), input.end());
    inputVector.push_back('\0');
    char* input_ptr = &inputVector[0];
    char** input_pptr = &input_ptr;
    return input_pptr;
}

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
    CHECK_THROWS_AS(parseOptions(0, createArgvInput("Test_parseOptions()")), std::exception);
    
    char** input = createArgvInput("image.png audio.ogg");
    auto filepaths = parseOptions(0, input); 
    map<int, string> expectedPaths = { {0, "image.png"}, {1, "audio.ogg"}};

    //auto filepaths = parseOptions(0, inputPptr); 

    
    CHECK(key_compare(expectedPaths, filepaths));

  } 
}
