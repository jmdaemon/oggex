#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Image.h"

using namespace std;
namespace fs = std::filesystem; 

struct DataFixture {
  const std::string IMAGE_FILENAME  = "../../inputFile2.png";
  Image::ImageData image{};

  DataFixture() : image(Image::ImageData(IMAGE_FILENAME)) { }
}; 

TEST_CASE_FIXTURE(DataFixture, "Outputfilename should be properly formatted") {
  std::string output = image.createOutputFilename();
  REQUIRE(output == "inputFile2-embed.png");
}

TEST_CASE_FIXTURE(DataFixture, "Image should be under 4 MiB") {
  CHECK(under4MiB(IMAGE_FILENAME));
}
