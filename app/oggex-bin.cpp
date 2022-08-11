#include "oggex.h"
#include "cli.h"

int main(int argc, char **argv) {

  // Parse arguments
  struct arguments arguments = set_default_args();
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  char* command = arguments.args[0];

  Sound sound = arguments.sound;
  Settings settings = { 10, false };
  Media media = {sound, settings, arguments};

  // Error checking
  if (!file_exists(sound.src))
    fmt::print("{}", "You must provide a valid .ogg audio file.");

  if (!file_exists(sound.image))
    fmt::print("{}", "You must provide a valid image file. Supported image formats are: PNG, JPG, JPEG and GIF.");

  if (sizeof(sound.tag) == 0)
    fmt::print("{}", "You cannot have an empty sound tag");
  
  // Handle commands
  if (strcmp(command, "embed") == 0)
    embed(media);
  else if (strcmp(command, "extract") == 0)
    extract(media);

  return 0;
}
