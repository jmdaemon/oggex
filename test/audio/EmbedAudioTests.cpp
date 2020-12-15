#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

#include "EmbedAudio.h"
#include <string>

int main(int argc, char** argv) {
  return 0;
}

TEST_CASE("Audio files can be embedded into image files") {
  SUBCASE("Test toLowerCase") {
    REQUIRE(toLowerCase("ABC") == "abc");
    REQUIRE(toLowerCase(".JPG") == ".jpg");
    CHECK(toLowerCase(".JPEG") == ".jpeg");
    CHECK(toLowerCase(".PNG") == ".png");
  }
}
