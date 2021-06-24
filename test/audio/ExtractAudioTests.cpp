#include "doctest.h"
#include "ExtractAudio.h"

using namespace std;
namespace fs = std::filesystem;

struct DataFixture {
  const std::string EMBEDDED_FILENAME  = "../../inputFile1.png";

  Image::ImageData image{};
  Options options;
  Data data{};

  DataFixture() : image(Image::ImageData(EMBEDDED_FILENAME)), data(createExtractData(image, options)) { }
};


TEST_CASE_FIXTURE(DataFixture, "getOffset()") {
  size_t offset = getOffset(EMBEDDED_FILENAME);
  REQUIRE(offset != 0);

  offset = getOffset("SearchTermUnavailable");
  REQUIRE(offset == 0);
}

TEST_CASE_FIXTURE(DataFixture, "findSoundTag should return sound tag in embedded file") { 
  std::filesystem::path image = data.image.getImage();
  string embeddedFileData   = dataToString(image, 0);
  size_t audioOffset        = getOffset(image);
  std::string soundTag      = findSoundTag(data, embeddedFileData, audioOffset);
  REQUIRE(!soundTag.empty());
  embeddedFileData          = dataToString(image, sizeOf(image));
  soundTag                  = findSoundTag(data, embeddedFileData, sizeOf(image));
  REQUIRE(soundTag.empty());
}

TEST_CASE_FIXTURE(DataFixture, "extract()") { 
  REQUIRE(extract(data) == 0);
} 
