#pragma once
#ifndef CMD_H
#define CMD_H

#include <string>
#include <map>
#include <tuple>

#include <fmt/core.h>

/**
  * Important uses for library:
  * - Show program usage (and be as customizable as Argp)
  * - Create commands that directly map to functions.
  * - Set sane defaults for arguments.
  */

/**
  * acceptsArg:
  * 0: Accepts None
  * 1: Accepts an optional argument
  * 2: Accepts 1 Argument.
  * 3: ...
  */
struct Option {
  //const char* longflag;
  const char* name;
  //const short shortflag;
  const int key;
  int acceptsArg;
  const char* arg;
  const char* help;
};

struct Command {
  const char* name;
};

static const struct Option options [] = {
  {"help"     , 'h', 0, 0, "Show this help message"},
  {"verbose"  , 'v', 0, 0, "Display program output and debugging information"},
  {"audio"    , 'a', 2, 0, "Sound file path"},
  {"image"    , 'i', 2, 0, "Image file path"},
  {"tag"      , 't', 2, 0, "Sound tag caption"},
  {"readable" , 'r', 0, 0, "Display human readable file sizes in logs"},
  {"format"   , 400, 2, 0, "Use either SI or binary unit sizes in logs"},
  //{"si"       , 400, 0, "Show file sizes using SI size units"},
  //{"bi"       , 500, 0, "Show file sizes using binary size units"},
};

static const struct Option embedOptions[] = {
  {"mono"   , 'm', 0, 0, "Use mono audio encoding"},
  {"output" , 'o', 2, 0, "Change output file name"},
};

static const struct Option extractOptions[] = {
  {"dest"   , 'd', 2, 0, "Change the destination folder"}
};

struct arguments {
  char *args[1]; /** command */
  int verbose;
  int scale;
};

void showUsage(std::string programName);
bool isEmpty(std::string arg, std::string errorMsg);
void formatPrintUsage(std::map<int, std::tuple<std::string, std::string, std::string>> flags);

#endif
