#include "../doctest-main.cpp"

#include <algorithm>
#include <filesystem>
#include <string>
#include <fstream>

//#include "EmbedAudio.h"
#include "ExtractAudio.h"

using namespace std;
namespace fs = std::filesystem;

TEST_CASE("Testing extract()") {
  const static size_t audioOffset = 19279;
  const static size_t fileSize = 2328969;
  fs::path filepath = "../../inputFile1.png";
  ifstream file(filepath, ifstream::in | ios::binary);

  SUBCASE("Retrieve the file, and filesize") {
  REQUIRE(sizeOf(file) != 0);

  //Make sure you open this file only once at the same time, c++ will block the file otherwise
  string filedata = dataToString(file);
  REQUIRE(!filedata.empty());
  CHECK(filedata.size() == fileSize);
  }

  SUBCASE("Returns start of ogg file in embedded file") {
    REQUIRE(getAudioOffset(file) !=  0);
    REQUIRE(getAudioOffset(file) != -1);
    CHECK(getAudioOffset(file) > 0);
  }

  SUBCASE("Returns sliced file after specified offset") {
    REQUIRE(!readFile(filepath, audioOffset).empty());
    CHECK(readFile(filepath, fileSize).empty());
    CHECK(readFile(filepath, audioOffset).length() == (fileSize - audioOffset));
  }

  SUBCASE("Retrieve sound tag from embedded file") {
    string soundTag = findSoundTag(filepath, audioOffset);
    REQUIRE(!soundTag.empty());
    REQUIRE(soundTag == "audio02");
    REQUIRE(soundTag.length() < 100);
  }

  REQUIRE(extract(filepath) == 0);
  file.close();
}
