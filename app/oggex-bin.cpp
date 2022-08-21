#include "oggex.h"

//#include "ogxlog.h"
//#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/cfg/env.h>
//#include <spdlog/fmt/bundled/core.h>
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
  //sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
  //auto logger = library::setup_logger(sinks);

  //auto l_app = spdlog::stdout_logger_mt(log_app);
  //auto l_lib = spdlog::stdout_logger_mt(log_lib);
  //sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>(spdlog::stdout_logger_st(log_app)));

  std::vector<spdlog::sink_ptr> sinks;
  //auto l_app = spdlog::stdout_logger_st(log_app);
  //sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>(l_app));
  //sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>(spdlog::stdout_logger_st(log_lib)));
  //sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
  //sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
  //sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_st>("logfile", 23, 59));

  auto logger = library::setup_logger(sinks);
  //spdlog::set_default_logger(logger);
  //spdlog::register_logger(l_lib);
  //spdlog::register_logger(l_app);

  // Set logging level
  //puts("Inputs:");
  //printf("%s\n", sound.src);
  //printf("%s\n", sound.image);
  //printf("%s\n", sound.tag);
  //printf("%s\n", sound.dest);

  //spdlog::set_level(spdlog::level::debug);
  spdlog::set_level(spdlog::level::level_enum::debug);
  //spdlog::set_level(spdlog::level::level_enum::trace);
  //spdlog::set_level(spdlog::level::debug);
  //spdlog::set_level(spdlog::level::level_enum::trace);
  library::info("message lib 1"); // No logging

  //spdlog::set_level(spdlog::level::level_enum::trace);
  //library::debug("message lib 2"); // No logging
  //spdlog::set_level(spdlog::level::level_enum::trace);
  //spdlog::set_level(spdlog::level::level_enum::debug);
  spdlog::set_level(spdlog::level::level_enum::trace);
  library::trace("message lib 1"); // No logging
  library::info("message lib 2"); // No logging
  library::debug("message lib 3"); // No logging
  library::warn("message lib 4"); // No logging
  library::error("message lib 5"); // No logging

  //spdlog::set_level(spdlog::level::level_enum::info);
  //spdlog::set_level(spdlog::level::level_enum::err);

  //if (arguments.verbose == 1)
    //spdlog::set_level(spdlog::level::trace);
  //else
    //spdlog::cfg::load_env_levels();

  //SPDLOG_ERROR("You must provide a valid image file. Supported image formats are: PNG, JPG, JPEG and GIF.");

  //spdlog::register_logger(logger);
  //spdlog::register_logger(spdlog::get(library::logger_name));

  // An image path must always be provided
  //if (sound.image != nullptr && !file_exists(sound.image))

  spdlog::info("Welcome to spdlog!");
  //SPDLOG_INFO("app 1");
  //SPDLOG_DEBUG("app 2");
  //SPDLOG_TRACE("app 3");
  //SPDLOG_ERROR("app 4");

  //SPDLOG_INFO("testing");

  //SPDLOG_DEBUG(fmt::format("sound.src   : {}", sound.src));
  //SPDLOG_DEBUG(fmt::format("sound.image : {}", sound.image));
  //SPDLOG_DEBUG(fmt::format("sound.dest  : {}", sound.dest));

  //SPDLOG_DEBUG("sound.src   : {}", sound.src);
  //SPDLOG_DEBUG("sound.image : {}", sound.image);
  //SPDLOG_DEBUG("sound.dest  : {}", sound.dest);

  //spdlog::debug("sound.src   : {}", (void*) sound.src);
  //spdlog::debug("sound.image : {}", (void*) sound.image);
  //spdlog::debug("sound.dest  : {}", (void*) sound.dest);


  //SPDLOG_LOGGER_DEBUG(library::logger_name, "sound.src   : {}", sound.src);
  //SPDLOG_LOGGER_DEBUG(library::logger_name, "sound.image : {}", sound.image);
  //SPDLOG_LOGGER_DEBUG(library::logger_name, "sound.dest  : {}", sound.dest);

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
