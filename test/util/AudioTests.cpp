#include "doctest.h"

#include <string>
#include <filesystem>

#include "Audio.h"

using namespace std;
namespace fs = std::filesystem;

struct DataFixture {
  Audio::AudioData audio;
};

TEST_CASE("Sound tags should be formatted correctly") { 
    string soundTag = "audio02";
    string overflowTag = "====================================================================================================";
    REQUIRE(formatSoundTag(soundTag) == "[" + soundTag + "]");
    REQUIRE(formatSoundTag(overflowTag) == "[" + overflowTag + "]");
    CHECK(formatSoundTag(overflowTag) == "********"); // Check to ensure that this test fails, and the tests are being run
}

//TEST_CASE("") {
//}
