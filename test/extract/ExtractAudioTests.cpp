#include "../doctest-main.cpp"

#include <filesystem>
#include <string>
#include <fstream>

#include "EmbedAudio.h"
#include "ExtractAudio.h"

using namespace std;
namespace fs = std::filesystem;

TEST_CASE("Testing extract()") {
  const static size_t audioOffset = 19279;
  const static size_t fileSize = 2328969;
  fs::path filepath = "../../inputFile1.png";
  ifstream file(filepath, ifstream::in | ios::binary);

  //SUBCASE("Retrieve the file, and filesize") {
  //REQUIRE(getFileSize(file) != 0);
  //REQUIRE(dataToString(file) != 0);
  //}

  //SUBCASE("Returns start of ogg file in embedded file") {
    //REQUIRE(!(getAudioOffset(file) ==  0));
    //REQUIRE(!(getAudioOffset(file) == -1));
    //CHECK(getAudioOffset(file) > 0);
  //}

  //SUBCASE("Returns sliced file after specified offset") {
    //REQUIRE(readFile(filepath, audioOffset) != 0);
    //CHECK(readFile(filepath, fileSize).empty());
  //}

  SUBCASE("Retrieve sound tag from embedded file") {
    REQUIRE(!findSoundTag(filepath, audioOffset).empty());
    REQUIRE((findSoundTag(filepath, audioOffset)) == "audio02");
  }

  REQUIRE(extract(filepath) == 0);
}
