#pragma once
#ifndef OGGEX_CLI_H
#define OGGEX_CLI_H

/* Support header include for C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* Third Party Libraries */
#include "sound.h"

/* Standard Library */
#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pcre.h>
#include <math.h>

/** Author and maintainer's email. Contact me directly here for questions or bug reports, or use the issues page. */
static const char *email = "<josephm.diza@gmail.com>";

/** Program summary. */
static const char doc[] = "Oggex - Embed and extract OGG audio files in images using sound tags";

/** A description of the arguments we accept. */
static const char args_doc[] = "[embed/extract] [options]";

/** http://www.gnu.org/software/libc/manual/html_node/Argp-Option-Vectors.html <br> */
/** The options we understand. */
static const struct argp_option options[] = {
  {"version"  , 'V', 0, 0, "Show program version", 0},
  {"verbose"  , 'v', 0, 0, "Display program output and debugging information", 0},
  {"audio"    , 'a', 0, 0, "Sound file path", 0},
  {"image"    , 'i', 0, 0, "Image file path", 0},
  {"tag"      , 't', 0, 0, "Sound tag caption", 0},
  {"readable" , 'r', 0, 0, "Display human readable file sizes in logs", 0},
  {"mono"     , 'm', 0, 0, "Enable mono audio channel encoding", 0},
  {"nolimit"  , 'l', 0, 0, "Disables 4MiB limit for embedding files", 0},
  //{"format"   , 400, 0, 0, "Use either SI or binary unit sizes in logs", 0},
  {"si"     ,  500, 0,      0, "Display SI byte sizes", 0},
  {"bi"     ,  600, 0,      0, "Display binary byte sizes", 0},
  {}
  //{0}
};

/** Used by main to communicate with parse_opt. */
struct arguments {
  char *args[1]; /** from, to */
  bool readable;
  bool mono_encoding;
  bool nolimit;
  int verbose;
  int scale;
  Sound sound;
};

/** Parse a single option. */
error_t parse_opt (int key, char *arg, struct argp_state *state);

/** http://www.gnu.org/software/libc/manual/html_node/Argp-Parsers.html <br> */
/** http://www.gnu.org/software/libc/manual/html_node/Argp-Help-Filtering.html <br> */
/** Our argp parser. */
static const struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0};

/** Set default values for arguments */
struct arguments set_default_args();

#ifdef __cplusplus
}
#endif
#endif // OGGEX_CLI_H
