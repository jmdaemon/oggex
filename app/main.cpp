#include "ogx.h"

int main(int argc, char **argv) {
  struct arguments arguments = init_args(argc, argv);
  char* command = arguments.args[0];
  Media media = {arguments.sound, arguments.settings, arguments};
  setup_logging(arguments);
  oggex(command, media);
  return 0;
}
