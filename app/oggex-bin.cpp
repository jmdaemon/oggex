#include "oggex.h"

#include <spdlog/logger.h>
#include <spdlog/cfg/env.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>

int main(int argc, char **argv) {

  // Parse arguments
  struct arguments arguments = set_default_args();
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  char* command = arguments.args[0];

  Sound sound = arguments.sound;
  Settings settings = { 10, false };
  Media media = {sound, settings, arguments};

  // Setup libary logging sinks
  std::vector<spdlog::sink_ptr> sinks;
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());

  auto logger = library::setup_logger(sinks);

  if (arguments.verbose == 1)
    spdlog::set_level(spdlog::level::trace);
  else
    spdlog::cfg::load_env_levels();

  if (sound.image == nullptr || !file_exists(sound.image)) {
    SPDLOG_ERROR("You must provide a valid image file. Supported image formats are: PNG, JPG, JPEG and GIF.");
    exit(-1);
  }
    //library::error("You must provide a valid image file. Supported image formats are: PNG, JPG, JPEG and GIF.");
    //l_app->error("You must provide a valid image file. Supported image formats are: PNG, JPG, JPEG and GIF.");
  
  // Handle commands
  if (strcmp(command, "embed") == 0) {
    //if (sound.src != nullptr && !file_exists(sound.src))
    if (sound.src == NULL || !file_exists(sound.src)) {
      SPDLOG_ERROR("You must provide a valid .ogg audio file.");
      exit(-1);
    }
      //library::error("You must provide a valid .ogg audio file.");
      //l_app->error("You must provide a valid .ogg audio file.");

    if (sizeof(sound.tag) == 0) {
      SPDLOG_ERROR("You cannot have an empty sound tag");
      exit(-1);
    }
      //library::error("You cannot have an empty sound tag");
      //l_app->error("You cannot have an empty sound tag");

    //spdlog::shutdown();
    embed(media);
  } else if (strcmp(command, "extract") == 0) {
    //spdlog::shutdown();
    extract(media);
  }

  return 0;
}
