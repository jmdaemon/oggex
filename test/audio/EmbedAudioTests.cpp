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

//char** createArgvInput(vector<string> arguments) {
  ////std::vector<std::string> arguments = {"--dir", "/some_path"};

  //vector<char*> argv;
  //for (const auto& arg : arguments)
      //argv.push_back((char*)arg.data());
  //argv.push_back(nullptr);

  //f.bar(argv.size() - 1, argv.data());
  ////return argv;
//}
//vector<char*> createArgvInput(vector<string> arguments) {
map<int, string> createArgvInput(vector<string> arguments) {
    vector<string> firstTestArgs = {""};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);

    map<int, string> filepaths = parseOptions(argv.size() - 1, argv.data()); 
    return filepaths;
    //char** parseOptions
    //return argv;
}

TEST_CASE("Audio files can be embedded into image files") {
  SUBCASE("Test toLowerCase()") {
    INFO("Current outPut of toLowerCase(): ");

    REQUIRE(toLowerCase("ABC") == "abc");
    REQUIRE(toLowerCase(".JPG") == ".jpg");
    CHECK(toLowerCase(".JPEG") == ".jpeg");
    CHECK(toLowerCase(".PNG") == ".png");
  }

  SUBCASE("Testing parseOptions()") { 
    INFO("Current output of parseOptions: ");

    //vector<string> firstTestArgs = {""};
    //vector<char*> argv;
    //for (const auto& arg : arguments)
        //argv.push_back((char*)arg.data());
    //argv.push_back(nullptr);
    //vector<string> firstTestArgs = {""};
    vector<string> firstTestArgs = {""};
    //vector<char*> getArg = createArgvInput(firstTestArgs);
    //auto nullInput = parseOptions(argv.size() - 1, argv.data());
    CHECK_THROWS_AS(createArgvInput(firstTestArgs), std::exception);
    //char** nullInput = parseOptions(getArg.size() - 1, getArg.data());

    //CHECK_THROWS_AS(parseOptions(0, nullInput), std::exception);
    //CHECK_THROWS_AS(parseOptions(2, nullInput), std::exception);

    //CHECK_THROWS_AS(parseOptions(0, createArgvInput("")), std::exception);
    //CHECK_THROWS_AS(parseOptions(2, createArgvInput("")), std::exception);
    //CHECK_THROWS_AS(parseOptions(0, createArgvInput(firstTestArgs)), std::exception);
    //CHECK_THROWS_AS(parseOptions(2, createArgvInput(firstTestArgs)), std::exception);


    //vector<string> arguments = {"-i ", "image.png", "-a ", "audio.ogg"};
    vector<string> arguments = {"image.png", "audio.ogg"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
      //argv.push_back(arg.data());
    argv.push_back(nullptr);

    //f.bar(argv.size() - 1, argv.data());
    map<int, string> filepaths = parseOptions(argv.size() - 1, argv.data()); 
    //return argv;

    //vector<string> secondTestArgs = {"image.png", "audio.ogg"};
    
    //char** input = createArgvInput("image.png audio.ogg");
    //char** input = createArgvInput(secondTestArgs);

    //map<int, string> filepaths = parseOptions(2, input); 
    map<int, string> expectedPaths = { {0, "image.png"}, {1, "audio.ogg"}};
    ////map<int, string> expectedPaths = { {0, "image.png"}};

    //auto filepaths = parseOptions(0, inputPptr); 
    //auto filepaths = parseOptions(0, inputPptr); 
    //cout << filepaths[0] << endl;
    //cout << expectedPaths[0] << endl;
    CHECK(key_compare(expectedPaths, filepaths));

  } 
}
