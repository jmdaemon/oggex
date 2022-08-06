#pragma once
#ifndef OGGEX_MEDIA_H
#define OGGEX_MEDIA_H

#include "utility/Options.h"

/** Sound file */
struct Sound {
  char* src;  /* Sound file path */
  char* dest; /* Image name */
  char* temp;
  char* log;
  char* tag;
};

/** Audio Settings */
struct Settings {
  int quality;
  bool mono_channel;
};

struct Media {
  Sound sound;
  Settings settings;
  Options options{};
};

#endif // OGGEX_MEDIA_H
