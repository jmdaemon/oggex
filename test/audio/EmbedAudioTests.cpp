#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "EmbedAudio.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;


TEST_CASE("Audio files can be embedded into image files") {

  SUBCASE("Test toLowerCase()") {
    cout << "Testing toLowerCase()" << endl;
    INFO("Current outPut of toLowerCase(): ");

    REQUIRE(toLowerCase("ABC") == "abc");
    REQUIRE(toLowerCase(".JPG") == ".jpg");
    CHECK(toLowerCase(".JPEG") == ".jpeg");
    CHECK(toLowerCase(".PNG") == ".png");
  }

}
