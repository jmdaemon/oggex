#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Data.h"

struct DataFixture {
  Audio::AudioData audio;
  Image::ImageData image;
  Options options;
  Data data;
};


TEST_CASE("Data should display a key and value, with correct padding") {
  INFO("printSize() ");
}

TEST_CASE_FIXTURE(DataFixture, "Data should display a file size with correct padding") {
  INFO("printSize() ");
}
