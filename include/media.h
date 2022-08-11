#pragma once
#ifndef OGGEX_MEDIA_H
#define OGGEX_MEDIA_H

#include "sound.h"
#include "cli.h"

typedef struct Media {
  Sound sound;
  Settings settings;
  arguments args;
} Media;

#endif // OGGEX_MEDIA_H
