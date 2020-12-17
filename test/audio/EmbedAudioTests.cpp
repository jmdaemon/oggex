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
    map<int, string> expectedPaths = { {0, "image.png"}, {1, "audio.ogg"}};

    auto filepaths = parseOptions(0, inputPptr); 

    
    CHECK(key_compare(expectedPaths, filepaths));

    //map<int, string>::iterator it; 

    //for (it = expectedPaths.begin(); it != expectedPaths.end(); it++) { 
      ////CHECK(it->first == expectedPaths[key]);
      //CHECK(it->first == [key]);
    //}

    //for( const auto& paths_it : filepaths) {
        ////std::cout << sm_pair.first << '\n' ;
        //for( const auto& expect_it : paths_it.second )
          //CHECK(it->first == expect_it->first);
        //{
            ////std::cout << "     " << sc_pair.first << '{' << sc_pair.second.a << ',' 
                      ////<< sc_pair.second.b << ',' << sc_pair.second.d << "}\n" ;    
        //}
    //}

    //for (auto const& [key, path] : filepaths) {
      //CHECK(path == expectedPaths[key]);
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
