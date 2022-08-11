#pragma once
#ifndef OGGEX_MEDIA_H
#define OGGEX_MEDIA_H

#include "Options.h"
#include "sound.h"
#include "cli.h"

typedef struct Media {
  Sound sound;
  Settings settings;
  arguments args;
  Options options{};
} Media;

#endif // OGGEX_MEDIA_H
