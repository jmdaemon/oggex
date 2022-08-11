#pragma once
#ifndef OGGEX_MEDIA_H
#define OGGEX_MEDIA_H

#include "utility/Options.h"
#include "sound.h"
#include "cli.h"
//#include <argp.h>
//extern "C" {
//#include <stdio.h>
//#include <stdlib.h>
//#include <argp.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdbool.h>
//#include <pcre.h>
//#include <math.h>
//}
//#include "Version.h"
//#include "cli.h"
struct arguments;


typedef struct Media {
  Sound sound;
  Settings settings;
  arguments args;
  Options options{};
} Media;

#endif // OGGEX_MEDIA_H
