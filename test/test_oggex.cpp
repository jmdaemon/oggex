#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "oggex.h"
#include <unistd.h>
#include <limits.h>
#include <cstdarg>
#include "cli_defs.h"
#include <filesystem>

// Samples
const static std::string AUDIO_FILE = "audio02.ogg";
const static std::string IMAGE_FILE = "835127a09fc542aeb3bfa99c9d91972d.png.png";
const static std::string EMBED_FILE = "835127a09fc542aeb3bfa99c9d91972d.png";
const static std::string SOUND_TAG  = "audio02";

// Helper Functions
std::filesystem::path ls() {
    auto path = std::filesystem::current_path();
    fmt::print("Current Directory: {}\n", path.string());
    return path;
}

//char* stoc(std::string s) {
  //char* result = new char;
  //result = (char*) s.c_str();
  //return result;
//}

void show_sound(Sound sound) {
    printf("Source  : %s\n", sound.src);
    printf("Image   : %s\n", sound.image);
    printf("Dest    : %s\n", sound.dest);
    printf("Tag     : %s\n", sound.tag);
}

TEST_CASE("[Test] find_sound_tag finds sound tag offsets") {
  SUBCASE("find_sound_tag can find sound tag embedded in string") {
    // Note that this function is unable to find sound tags embedded like so:
    // ================[audio02]================
    // The end of the tag must be calculated beforehand with s_oggs
    std::string conts = std::string(50, '=') + '[' + SOUND_TAG + ']';
    auto expect = SOUND_TAG;
    auto result = find_sound_tag(conts);
    CHECK(expect == result);
  }
  
  SUBCASE("find_sound_tag can find sound tag embedded in file") {
    fmt::print("find_sound_tag\n");
    auto path = ls();
    if (path.stem().string() != "extract") {
      chdir("samples/extract");
      ls();
    }

    std::string filename = EMBED_FILE;
    auto embed_size = file_size(filename.c_str());
    auto s_oggs    = find_str_offset(filename.c_str(), OGG_ID_HEADER);

    fmt::print("embed_size: {}\n", embed_size);
    fmt::print("s_oggs    : {}\n", s_oggs);

    const char* contents = read_file(filename.c_str());
    std::string conts(contents, embed_size);

    auto expect = SOUND_TAG;
    auto result = find_sound_tag(conts.substr(0, s_oggs));

    fmt::print("Expected: {}\n", expect);
    fmt::print("Result  : {}\n", result);
    CHECK(expect == result);
  }
}

TEST_CASE("[Test] embed_size calculates final embedded file size") {
  // TODO: Test for 'Error: encoding failed' exception
  fmt::print("embed_size\n");
  auto path = ls();
  if (path.stem().string() == "extract") {
    chdir("../..");
    ls();
  }

  // Initialize dummy sound struct
  auto file = "LICENSE";
  //Sound sound = { .src = stoc(file), .image = stoc(file), .tag = stoc(SOUND_TAG) };
  Sound sound = { .src = (char*) file, .image = (char*) file, .tag = (char*)SOUND_TAG.c_str() };
  auto expect = file_size(sound.src) * 2 + SOUND_TAG.length() +1;
  auto result = embed_size(sound);
  CHECK(expect == result);
}

TEST_CASE("[Test] format_command returns valid ffmpeg commands") {
  Sound sound = {
    .src = (char*) "aaaa", .image = (char*) "bbbb",
    .temp = (char*) "temp.ogg", .log = (char*) "log.txt", .tag = (char*) "cccc"
  };
  Settings settings = {10, false};
  Media media = { sound, settings, {}};
  auto expect = fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1", sound.src, settings.quality, "", sound.temp, sound.log);
  show_sound(sound);

  auto result = format_command(media);
  CHECK(expect == result);

  //delete sound.src;
  //delete sound.image;
  //delete sound.temp;
  //delete sound.log;
  //delete sound.tag;
}

TEST_CASE("[Test] encodeAudio runs ffmpeg command and generates temp.ogg, log.txt") {
  // TODO: Test for exception thrown
  // TODO: Test for audio limit
  fmt::print("embed_size\n");
  auto path = ls();
  if(path.stem().string() == "extract") {
    chdir("../..");
    chdir("samples/embed");
    path = ls();
    if (path.stem().string() != "embed") {
      fmt::print("Not in correct directory for encodeAudio test");
      exit(1);
    }
  } else if (path.stem().string() != "embed") {
    chdir("samples/embed");
  }

  Sound sound = {.src = (char*) AUDIO_FILE.c_str(), .image = (char*) IMAGE_FILE.c_str(),
    .temp = (char*) "temp.ogg", .log = (char*) "log.txt", .tag = (char*) SOUND_TAG.c_str()
  };
  Settings settings = {10, false};
  struct arguments args = { .nolimit = true };
  Media media = { sound, settings, args};
  show_sound(sound);

  encodeAudio(media);
  CHECK(file_exists("temp.ogg"));
  CHECK(file_size("temp.ogg") != 0);
  CHECK(file_exists("log.txt"));
  CHECK(file_size("log.txt") != 0);
  remove("temp.ogg");
  remove("log.txt");

  //delete sound.src;
  //delete sound.image;
  //delete sound.temp;
  //delete sound.log;
  //delete sound.tag;
}

//TEST_CASE("[Test] encodeAudio runs ffmpeg command and generates temp.ogg, log.txt") {
  //Sound sound = {
    //.src = ()

  //};
  ////Sound sound = {
    ////.src = (char*) "aaaa", .image = (char*) "bbbb",
    ////.temp = (char*) "temp.ogg", .log = (char*) "log.txt",
    ////.tag = (char*) (char*) (char*) (char*) (char*) (char*) (char*) (char*) (char*) "cccc"
  ////};
  //Settings settings = {10, false};
  //Media media = { sound, settings, {}};
  //auto expect = fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1", sound.src, settings.quality, "", sound.temp, sound.log);
  //auto result = format_command(media);
  //CHECK(expect == result);
//}


// Check encodeAudio, encodeImage, encode, extract
/**
  * TODO:
  * Tests needing to be written:
  * - encode/encodeAudio
  * - encodeImage
  * - extract
  */
