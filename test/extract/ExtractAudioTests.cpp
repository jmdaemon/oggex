#include "../doctest-main.cpp"

#include "EmbedAudio.h"
#include "ExtractAudio.h"
#include <filesystem>

namespace fs = std::filesystem;
#include <string>

TEST_CASE("Testing extract()") {
  fs::path filepath = "../../inputFile1.png";
  CHECK(extract(filepath) == 0);
}
