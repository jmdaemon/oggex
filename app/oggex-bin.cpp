#include "ogx.h"

/** Initializes the spdlog logger */
std::shared_ptr<spdlog::logger> setup_logger(std::vector<spdlog::sink_ptr> sinks) {
  auto logger = spdlog::get(logger_name);
  if (!logger) {
    if (sinks.size() > 0) {
        logger = std::make_shared<spdlog::logger>(logger_name, std::begin(sinks), std::end(sinks));
        spdlog::register_logger(logger);
    } else {
        logger = spdlog::stdout_color_mt(logger_name);
    }
  }
  return logger;
}

/** Initializes spdlog logger, and toggles logging statements at runtime */
void setup_logging(arguments arguments) {
  // Setup library logging
  std::vector<spdlog::sink_ptr> sinks;
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
  auto logger = setup_logger(sinks);

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
}

int oggex(const char* command, Media media) {
  if (media.sound.image == nullptr || !file_exists(media.sound.image)) {
    SPDLOG_ERROR("You must provide a valid image file. Supported image formats are: PNG, JPG, JPEG and GIF.");
    exit(-1);
  }
  
  // Handle oggex commands
  if (strcmp(command, "embed") == 0) {
    if (media.sound.src == nullptr || !file_exists(media.sound.src)) {
      SPDLOG_ERROR("You must provide a valid .ogg audio file.");
      exit(-1);
    }

    if (sizeof(media.sound.tag) == 0) {
      SPDLOG_ERROR("You cannot have an empty sound tag");
      exit(-1);
    }

    embed(media);
  } else if (strcmp(command, "extract") == 0)
    extract(media);
  return 0;
}

/** Parses command line arguments */
arguments init_args(int argc, char** argv) {
  struct arguments arguments = set_default_args();
  argp_parse (&argp, argc, argv, 0, 0, &arguments);
  return arguments;
}

// For GUI executables
const char* COMMAND_PLACEHOLDER = "placeholder";

/** Initializes the arguments struct for gui binaries
  * 
  * Argp will error out if args.args[0] is null.
  * This is intended functionality for oggex but not for oggex-qt or oggex-gtk.
  * This function allows us to skip this check for gui binaries by providing a dummy placeholder
  * value for the necessary arguments.
  *
  * At runtime in oggex-gtk or oggex-qt, we check for this placeholder to determine if we should
  * do the embed/extract the same as oggex cli would, or to display the gui.
  *
  * Note that we cannot setup the logger here, since it will be linked later in
  * the gui executables and will cause problems otherwise.
  */
arguments init_args_gui(int argc, char** argv) {
  struct arguments args;
  // Setup placeholder value
	args.args[0] = (char*) COMMAND_PLACEHOLDER;
	args = set_default_args();
	argp_parse(&argp, argc, argv, 0, 0, &args);
  return args;
}

/* Determine if the command was the placeholder value, or real user input */
bool cmd_specified(struct arguments args) {
  bool cmd_was_given = (strcmp(args.args[0], COMMAND_PLACEHOLDER) != 0) ? true : false;
  return cmd_was_given;
}
