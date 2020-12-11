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
  //CHECK(embedInImage("../../resources/12727a5f30b1429a1fd35113fd2550d8.png", "./dummy/directory") == true);
  CHECK(embedInImage("./12727a5f30b1429a1fd35113fd2550d8.png", "./dummy/directory") == true);
  // Fill in with files of various formats.
}
