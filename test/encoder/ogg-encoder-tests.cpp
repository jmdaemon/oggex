#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <string>
#include <stdlib.h>

bool embedInImage(std::string imgPath, std::string oggPath) {
  return embedInImage(imgPath, oggPath);
}

int main(int argc, char** argv) {
  return 0;
}

TEST_CASE( "OGG file is embedded in image") {
  CHECK(embedInImage("inputFile1.png", "outputFile.png") == true);
  //CHECK(getTags("inputFile1") != 0);
}
