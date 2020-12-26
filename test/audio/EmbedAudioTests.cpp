#include "../doctest-main.cpp"

#include "EmbedAudio.h"
#include "File.h"
#include "Image.h"

using namespace std;
namespace fs = std::filesystem;

TEST_CASE("Audio files can be embedded into image files") {
  fs::path filepath = "../../inputFile1.png";
  ifstream file(filepath, ifstream::in | ios::binary);

  SUBCASE("Test toLowerCase()") {
    INFO("Current outPut of toLowerCase(): ");

    REQUIRE(File::toLowerCase("ABC") == "abc");
    REQUIRE(File::toLowerCase(".JPG") == ".jpg");
    CHECK(File::toLowerCase(".JPEG") == ".jpeg");
    CHECK(File::toLowerCase(".PNG") == ".png");
  }
  SUBCASE("Temp files should be removed") {
  }

  SUBCASE("Sound tags should be formatted correctly") {
    string soundTag = "audio02";
    string overflowTag = "====================================================================================================";
    REQUIRE(tagUnder100(soundTag.length()));
    REQUIRE(formatAudioTags(soundTag)[0] == "[audio02]");
    CHECK(!tagUnder100(overflowTag.length()));
  }

  //embed();
  file.close();
}
