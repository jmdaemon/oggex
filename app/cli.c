#include "cli.h"
#include "Version.h"

struct arguments set_default_args() {
  struct arguments arguments;

  /* Default values. */
  arguments.verbose = 0;
  arguments.scale = 1000;
  arguments.readable = false;
  arguments.nolimit = false;

  /* Sound */
  arguments.sound.temp = "temp.ogg";
  arguments.sound.log = "log.txt";
  /*arguments.sound.temp = (char*) "temp.ogg";*/
  /*arguments.sound.log = (char*) "log.txt";*/

  /* Settings */
  arguments.settings.quality = 10;
  arguments.settings.mono_channel = false;
  return arguments;
}

error_t parse_opt (int key, char *arg, struct argp_state *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;
  switch (key) {
    case 'V':
      printf("oggex %s v%d.%d.%d\n", email, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
      exit(0);

    case 'v':
      arguments->verbose = 1;
      break;

    case 'a':
      arguments->sound.src = arg;
      break;

    case 'i':
      arguments->sound.image = arg;
      break;

    case 't':
      arguments->sound.tag = arg;
      break;

    case 'd':
      arguments->sound.dest = arg;
      break;

    case 'r':
      arguments->readable = true;
      break;

    case 'm':
      arguments->settings.mono_channel = true;
      break;

    case 'l':
      arguments->nolimit = true;
      break;
    
    case 400:
      if (strcmp(arg, "bi") == 0)
        arguments->scale = 1024;
      break;

    case ARGP_KEY_ARG:
      /*if (state->arg_num > 1)*/
        /* Too many arguments. */
        /*argp_usage (state);*/
      arguments->args[state->arg_num] = arg;
      break;

    case ARGP_KEY_END:
      /*if (state->arg_num < 1) {*/
        /* Not enough arguments. */
        /*argp_usage (state);*/
      /*}*/
      break;

    default:
      return ARGP_ERR_UNKNOWN;

    }
  return 0;
}
