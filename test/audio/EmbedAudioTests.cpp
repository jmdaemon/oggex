#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "EmbedAudio.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

//std::string testShowUsage(std::string programName) {
  //stringstream buffer;
  //streambuf *sbuf = std::cerr.rdbuf();
  //cerr.rdbuf(standardOutput.rdbuf());
  //showUsage(programName);
  //string result = standardOutput.str();
  //cout << result;
  //return result;
//}

//string showUsageOutput(std::string programName) {
  //stringstream ss;
   //ss  << "Usage:" << programName << " [audio_file] [image_file]\n"
       //<< "Options:\n"
       //<< "\t-h, --help\t\tShow this help message\n"
       //<< "\t-f, --fast\t\tLower image quality\n"
       ////<< "Fuck my shit up"
       //<< std::endl;
   //std::cout << ss.str();
   //return ss.str();
//}

//void logToFile(std::string fileName) { 
  //ofstream log_file(fileName, std::ios::binary);

//}

//void redirectOutput() {
  //streambuf* originalCerrStreamBuf = cerr.rdbuf();
  //ostringstream strCerr;
  //cout.rdbuf( strCerr.rdbuf() ); 
//}

TEST_CASE("Audio files can be embedded into image files") {

  SUBCASE("Test toLowerCase()") {
    cout << "Testing toLowerCase()" << endl;
    INFO("Current outPut of toLowerCase(): ");

    REQUIRE(toLowerCase("ABC") == "abc");
    REQUIRE(toLowerCase(".JPG") == ".jpg");
    CHECK(toLowerCase(".JPEG") == ".jpeg");
    CHECK(toLowerCase(".PNG") == ".png");
  }

  //SUBCASE("Test showUsage()") {
    //REQUIRE(testShowUsage("oggex") == showUsageOutput("oggex"));
  //}
}
