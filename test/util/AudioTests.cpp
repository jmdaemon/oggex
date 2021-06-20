#include "doctest.h"

#include <iostream>
#include <string>
#include <filesystem>

#include "Audio.h"

using namespace std;
namespace fs = std::filesystem;

struct DataFixture {
  Audio::AudioData audio;
};

TEST_CASE("Testing Audio file class") {
    SUBCASE("") {
    }
}

TEST_CASE("Sound tags should be formatted correctly") {
    string soundTag = "audio02";
    string overflowTag = "====================================================================================================";
    //REQUIRE(tagUnder100(soundTag.length()));
    REQUIRE(formatSoundTag(soundTag) == "[audio02]");
    //CHECK(!tagUnder100(overflowTag.length()));
}

//TEST_CASE("") {
//}
