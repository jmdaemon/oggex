#pragma once
#ifndef OGGEX_MEDIA_H
#define OGGEX_MEDIA_H

#include "cli_defs.h"

/* Support header include for C++ */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct Media {
  Sound sound;
  Settings settings;
  arguments args;
} Media;

#ifdef __cplusplus
}
#endif

#endif // OGGEX_MEDIA_H
