#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Cmd.h"

//TEST_CASE("showUsage()") { 
  //freopen("showUsage.txt", "w", stderr);
  //std::string output = dataToString("showUsage.txt");
  //CHECK(!output.empty());
//}

TEST_CASE("isEmpty()") {
  std::string cmdArg = "-a";
  std::string errorMsg = "Audio file not specified.";
  REQUIRE(!isEmpty(cmdArg, errorMsg));
  cmdArg = "";
  REQUIRE(isEmpty(cmdArg, errorMsg));
}
