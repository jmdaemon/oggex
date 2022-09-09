#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "oggex.h"
#include <unistd.h>
#include <limits.h>
#include <cstdarg>
#include "cli_defs.h"

// Samples
const static std::string AUDIO_FILE = "audio02.ogg";
const static std::string IMAGE_FILE = "835127a09fc542aeb3bfa99c9d91972d.png.png";
const static std::string EMBED_FILE = "835127a09fc542aeb3bfa99c9d91972d.png";
const static std::string SOUND_TAG  = "audio02";

// Helper Functions

TEST_CASE("[Test] find_sound_tag finds sound tag offsets") {
  SUBCASE("find_sound_tag can find sound tag embedded in string") {
    auto conts = std::string(50, '=') + "[" + SOUND_TAG + "]" + std::string(50, '=');
    auto expect = SOUND_TAG;
    auto result = find_sound_tag(conts);
    CHECK(expect == result);
  }
  
  SUBCASE("find_sound_tag can find sound tag embedded in file") {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    fmt::print("Current Directory: {}\n", cwd);

    std::string filename = fmt::format("{}/samples/extract/{}", cwd, EMBED_FILE);
    auto embed_size = file_size(filename.c_str());
    auto s_oggs    = find_str_offset(filename.c_str(), OGG_ID_HEADER);

    auto contents = read_file(filename.c_str());
    std::string conts(contents, embed_size);
    auto expect = SOUND_TAG;
    auto result = find_sound_tag(conts.substr(0, s_oggs));
    CHECK(expect == result);
  }
}

TEST_CASE("[Test] embed_size calculates final embedded file size") {
  // Initialize dummy sound struct
  Sound sound;
  auto src = "LICENSE";
  auto image = "LICENSE";
  sound.src = (char*) src;
  sound.image  = (char*) image;
  sound.tag = (char*) SOUND_TAG.c_str();

  auto expect = file_size(src) * 2 + SOUND_TAG.length() +1;
  auto result = embed_size(sound);
  CHECK(expect == result);
}

TEST_CASE("[Test] format_command returns valid ffmpeg commands") {
  Sound sound = {
    .src = (char*) "aaaa", .image = (char*) "bbbb",
    .temp = (char*) "temp.ogg", .log = (char*) "log.txt",
    .tag = (char*) (char*) (char*) (char*) (char*) (char*) (char*) (char*) (char*) "cccc"
  };
  Settings settings = {10, false};
  arguments args;
  args.mono_encoding = false;
  Media media = { sound, settings, args };
  auto expect = fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1", sound.src, settings.quality, "", sound.temp, sound.log);
  auto result = format_command(media);
  CHECK(expect == result);
}

// Check encodeAudio, encodeImage, encode, extract
/**
  * TODO:
  * Tests needing to be written:
  * - format_command
  * - encode/encodeAudio
  * - encodeImage
  * - extract
  */
