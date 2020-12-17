#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "EmbedAudio.h"
#include <string>
#include <sstream>
#include <iostream>

std::string testShowUsage(std::string programName) {
  std::stringstream standardOutput;
  std::streambuf *sbuf = std::cerr.rdbuf();
  std::cerr.rdbuf(standardOutput.rdbuf());
  showUsage(programName);
  std::string result = standardOutput.str();
  std::cout << result;
  return result;
}

std::string showUsageOutput(std::string programName) {
  std::stringstream ss;
   ss  << "Usage:" << programName << " [audio_file] [image_file]\n" << "Fail this test intentionally"
       << "Options:\n"
       << "\t-h, --help\t\tShow this help message\n"
       << "\t-f, --fast\t\tLower image quality\n"
       //<< "Fuck my shit up"
       << std::endl;
   std::cout << ss.str();
   return ss.str();
}


TEST_CASE("Audio files can be embedded into image files") {

  SUBCASE("Test toLowerCase()") {
    INFO("Current outPut of toLowerCase(): ");
    REQUIRE(toLowerCase("ABC") == "abc");
    //REQUIRE(toLowerCase("ccc") == "abc");
    CAPTURE(toLowerCase("ABC"));

    REQUIRE(toLowerCase(".JPG") == ".jpg");
    CAPTURE(toLowerCase(".JPG"));
    //capture();

    CHECK(toLowerCase(".JPEG") == ".jpeg");
    CAPTURE(toLowerCase(".JPEG"));

    //capture();

    CHECK(toLowerCase(".PNG") == ".png");
    CAPTURE(toLowerCase(".PNG"));
    //capture();
  }

  SUBCASE("Test showUsage()") {
    REQUIRE(testShowUsage("oggex") == showUsageOutput("oggex"));
  }
}
