#pragma once
#ifndef OGGEX_CLI_DEFS_H
#define OGGEX_CLI_DEFS_H

#include "sound.h"

/* Support header include for C++ */
#ifdef __cplusplus
extern "C" {
#endif

/** Used by main to communicate with parse_opt. */
struct arguments {
  char *args[1]; /** embed, extract */
  bool readable;
  bool nolimit;
  int verbose;
  int scale;
  Sound sound;
  Settings settings;
};

#ifdef __cplusplus
}
#endif

#endif // OGGEX_CLI_DEFS_H
