#include "doctest.h"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <map>

#include "Cmd.h"

using namespace std;
namespace fs = std::filesystem;

bool quality;

template <typename Map>
bool key_compare (Map const &lhs, Map const &rhs) {
    return lhs.size() == rhs.size()
        && equal(lhs.begin(), lhs.end(), rhs.begin(), 
                      [] (auto a, auto b) { return a.first == b.first; });
}

//map<int, string> createArgvInput(vector<string> arguments) {
    //vector<string> firstTestArgs = {""};
    //vector<char*> argv;
    //for (const auto& arg : arguments)
        //argv.push_back((char*)arg.data()); argv.push_back(nullptr);

    ////map<int, string> filepaths = parseOptions(argv.size() - 1, argv.data(), quality); 
    //return filepaths;
//}

TEST_CASE("Command line arguments can be passed into embed") {
  SUBCASE("Testing parseOptions()") { 
    INFO("Current output of parseOptions: ");

    //vector<string> firstTestArgs = {""};
    //CHECK_THROWS_AS(createArgvInput(firstTestArgs), std::exception);

    //vector<string> secondTestArgs = {"image.png", "audio.ogg", "[soundTag]"};
    //map<int, string> expectedPaths = {{0, "image.png"}, {1, "audio.ogg"}, {2, "[soundTag]"}};
    //CHECK(key_compare(expectedPaths, createArgvInput(secondTestArgs)));
  } 
}
