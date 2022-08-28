#pragma once
#ifndef OGGEX_SOUND_H
#define OGGEX_SOUND_H

#include <string.h>
#include <stdbool.h>

/* Support header include for C++ */
#ifdef __cplusplus
extern "C" {
#endif

/** Sound file */
typedef struct Sound {
  char* src;   /* Sound file path */
  char* dest;  /* Destination directory */
  char* image; /* Image file path */
  char* temp;  /* Audio file path */
  char* log;   /* Log file path */
  char* tag;   /* Sound tag */
} Sound;

/** Audio Settings */
typedef struct Settings {
  int quality;
  bool mono_channel;
} Settings;

#ifdef __cplusplus
}
#endif

#endif // OGGEX_SOUND_H
