#pragma once
#ifndef OGGEX_MEDIA_H
#define OGGEX_MEDIA_H

#include "cli_defs.h"

typedef struct Media {
  Sound sound;
  Settings settings;
  arguments args;
} Media;

#endif // OGGEX_MEDIA_H
