#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

#include <string>
#include <stdlib.h>

bool embedInImage(std::string imgPath, std::string oggPath) {
  return embedInImage(imgPath, oggPath);
}

int main(int argc, char** arv) {
  return 0;
}

TEST_CASE( "OGG file is embedded in image") {
  CHECK(embedInImage("inputFile1.png", "outputFile.png") == true);
  // Fill in with files of various formats.
}
