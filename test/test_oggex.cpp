#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "oggex.h"
#include <unistd.h>
#include <limits.h>
#include <cstdarg>

// Samples
const static std::string AUDIO_FILE = "audio02.ogg";
const static std::string IMAGE_FILE = "835127a09fc542aeb3bfa99c9d91972d.png.png";
const static std::string EMBED_FILE = "835127a09fc542aeb3bfa99c9d91972d.png";
const static std::string SOUND_TAG  = "audio02";

// Helper Functions

TEST_CASE("[Test] find_sound_tag finds sound tag offsets") {
  auto conts = std::string(50, '=') + "[" + SOUND_TAG + "]" + std::string(50, '=');
  auto expect = SOUND_TAG;
  auto result = find_sound_tag(conts);
  CHECK(expect == result);
}

TEST_CASE("[Test] embed_size calculates final embedded file size") {
  // Initialize dummy sound struct
  Sound sound;
  auto src = "LICENSE";
  auto image = "LICENSE";
  sound.src = (char*) src;
  sound.image  = (char*) image;
  sound.tag = (char*) SOUND_TAG.c_str();

  auto expect = file_size(src) * 2 + SOUND_TAG.length();
  auto result = embed_size(sound);
  CHECK(expect == result);
}

//TEST_CASE("[Test] format_command returns valid ffmpeg commands") {
//}

// Check encodeAudio, encodeImage, encode, extract
/**
  * TODO:
  * Tests needing to be written:
  * - format_command
  * - embed_size
  * - encode/encodeAudio
  * - encodeImage
  * - getOffset
  * - findSoundTag
  * - extract
  */
