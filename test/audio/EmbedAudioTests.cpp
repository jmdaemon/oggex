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

//template <typename Map>

//bool key_compare (Map const &lhs, Map const &rhs) {
    //return lhs.size() == rhs.size()
        //&& std::equal(lhs.begin(), lhs.end(), rhs.begin(), 
                      //[] (auto a, auto b) { return a.first == b.first; });
//}

//map<int, string> createArgvInput(vector<string> arguments) {
    //vector<string> firstTestArgs = {""};
    //vector<char*> argv;
    //for (const auto& arg : arguments)
        //argv.push_back((char*)arg.data()); argv.push_back(nullptr);

    //map<int, string> filepaths = parseOptions(argv.size() - 1, argv.data()); 
    //return filepaths;
//}

TEST_CASE("Audio files can be embedded into image files") {
  SUBCASE("Test toLowerCase()") {
    INFO("Current outPut of toLowerCase(): ");

    REQUIRE(File::toLowerCase("ABC") == "abc");
    REQUIRE(File::toLowerCase(".JPG") == ".jpg");
    CHECK(File::toLowerCase(".JPEG") == ".jpeg");
    CHECK(File::toLowerCase(".PNG") == ".png");
  }

  //SUBCASE("Testing parseOptions()") { 
    //INFO("Current output of parseOptions: ");

    //vector<string> firstTestArgs = {""};
    //CHECK_THROWS_AS(createArgvInput(firstTestArgs), std::exception);

    //vector<string> secondTestArgs = {"image.png", "audio.ogg"};
    
    //map<int, string> expectedPaths = { {0, "image.png"}, {1, "audio.ogg"}};
    //CHECK(key_compare(expectedPaths, createArgvInput(secondTestArgs)));
  //} 

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
