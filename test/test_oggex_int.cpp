#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "oggex.h"
#include <unistd.h>
#include <limits.h>
#include <cstdarg>

#include "oggex_int.h"

// Samples
const static std::string AUDIO_FILE = "audio02.ogg";
const static std::string IMAGE_FILE = "835127a09fc542aeb3bfa99c9d91972d.png.png";
const static std::string EMBED_FILE = "835127a09fc542aeb3bfa99c9d91972d.png";
const static std::string SOUND_TAG  = "audio02";

// Helper Functions
std::string formatPath(const char* cwd, const std::string path) {
  return fmt::format("{}/{}", cwd, path);
}

std::string fmtEmbedCommand(std::string command, std::string audio, std::string image, std::string tag) {
  return fmt::format("{} embed -a {} -i {} -t {}", command, audio, image, tag);
}

std::string fmtExtractCommand(std::string command, std::string embed) {
  return fmt::format("{} extract -i {}", command, embed);
}

void run_embed_test(std::string bin, std::string audio, std::string image, std::string tag, std::string embed) {
    auto command = fmtEmbedCommand(bin, audio, image, tag);
    fmt::print("{}\n", command);

    system(command.c_str());
    const char* file = embed.c_str();
    CHECK(file_exists(file) != false);
    remove(file);
}
void run_extract_test(std::string bin, std::string audio, std::string image, std::string embed) {
    auto command = fmtExtractCommand(bin, embed);
    fmt::print("{}\n", command);
    system(command.c_str());

    CHECK(file_exists(audio.c_str()));
    CHECK(file_exists(image.c_str()));
    remove(audio.c_str());
    remove(image.c_str());
}

/** Clean the teest output files */
void clean_test(const char* path, ...) {
    va_list args;
    va_start(args, path);
    while (*path != '\0') {
      remove(path);
    }
    va_end(args);
}

// Integration Tests
TEST_CASE("Test File Embedding") {
  char cwd[PATH_MAX];
  fmt::print("Test File Embedding\n");
  getcwd(cwd, sizeof(cwd));
  fmt::print("Current Directory: {}\n", cwd);

  chdir("samples/embed");
  getcwd(cwd, sizeof(cwd));
  fmt::print("Current Directory: {}\n", cwd);
  
  auto audio  = formatPath(cwd, AUDIO_FILE);
  auto image  = formatPath(cwd, IMAGE_FILE);
  auto embed  = formatPath(cwd, EMBED_FILE);
  auto tag    = SOUND_TAG;

  if (audio.empty() || image.empty() || embed.empty() || tag.empty()) {
    fmt::print("Cannot execute embed tests. Exiting.\n");
    exit(-1);
  }
  
  SUBCASE("oggex embed") {
    //auto bin = "../../app/oggex";
    //run_embed_test(bin, audio, image, tag, embed);
    run_embed_test(OGGEX_BIN, audio, image, tag, embed);
  }

  SUBCASE("oggex-gtk embed") {
    //auto bin = "../../app/gtk/src/oggex-gtk";
    //run_embed_test(bin, audio, image, tag, embed);
    run_embed_test(OGGEX_GTK, audio, image, tag, embed);
  }

  SUBCASE("oggex-qt embed") {
    //auto bin = "../../app/qt/oggex-qt";
    //run_embed_test(bin, audio, image, tag, embed);
    run_embed_test(OGGEX_QT, audio, image, tag, embed);
  }
}

TEST_CASE("File Extract Tests") {
  char cwd[PATH_MAX];
  fmt::print("Test File Extract\n");
  getcwd(cwd, sizeof(cwd));
  fmt::print("Current Directory: {}\n", cwd);

  chdir("samples/extract");
  getcwd(cwd, sizeof(cwd));
  fmt::print("Current Directory: {}\n", cwd);
  
  auto audio  = formatPath(cwd, AUDIO_FILE);
  auto image  = formatPath(cwd, IMAGE_FILE);
  auto embed  = formatPath(cwd, EMBED_FILE);

  SUBCASE("oggex extract") {
    //auto bin = "../../app/oggex";
    //run_extract_test(bin, audio, image, embed);
    run_extract_test(OGGEX_BIN, audio, image, embed);
  }

  //SUBCASE("oggex-gtk extract") {
    //auto bin = "../../app/gtk/src/oggex-gtk";
    //run_extract_test(bin, audio, image, embed);
  //}

  //SUBCASE("oggex-qt extract") {
    //auto bin = "../../app/qt/oggex-qt";
    //run_extract_test(bin, audio, image, embed);
  //}
}
