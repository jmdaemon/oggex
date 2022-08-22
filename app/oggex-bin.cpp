#include "oggex.h"

#include <spdlog/logger.h>
#include <spdlog/cfg/env.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

int main(int argc, char **argv) {
  // Parse arguments
  struct arguments arguments = set_default_args();
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  char* command = arguments.args[0];
  Sound sound = arguments.sound;
  Settings settings = { 10, false };
  Media media = {sound, settings, arguments};

  // Setup library logging
  std::vector<spdlog::sink_ptr> sinks;
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
  auto logger = library::setup_logger(sinks);

  // Enable/disable logging
  if (arguments.verbose == 1)
    spdlog::set_level(spdlog::level::level_enum::trace);
  else {
    // Default to no logging
    spdlog::set_level(spdlog::level::level_enum::off);
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_NONE
  }
  spdlog::cfg::load_env_levels();

  /* [2022-08-20 23:16:43.347] [debug] [app.cpp:3] Message! */
  spdlog::set_pattern("[%Y-%m-%d %H.%M.%S.%e] [%^%l%$] [%s:%#] %v");

  if (sound.image == nullptr || !file_exists(sound.image)) {
    SPDLOG_ERROR("You must provide a valid image file. Supported image formats are: PNG, JPG, JPEG and GIF.");
    exit(-1);
  }
  
  // Handle oggex commands
  if (strcmp(command, "embed") == 0) {
    if (sound.src == nullptr || !file_exists(sound.src)) {
      SPDLOG_ERROR("You must provide a valid .ogg audio file.");
      exit(-1);
    }

    if (sizeof(sound.tag) == 0) {
      SPDLOG_ERROR("You cannot have an empty sound tag");
      exit(-1);
    }

    embed(media);
  } else if (strcmp(command, "extract") == 0)
    extract(media);

  return 0;
}
