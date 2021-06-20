#include "Cmd.h"

#include <map>
#include <tuple>

void formatPrintUsage(std::map<int, std::tuple<std::string, std::string, std::string>> flags) {
  for (auto const& [key, flag] : flags) { 
    if (!std::get<1>(flag).empty()) {
      fmt::print(stderr, 
          "{:>8}{:<4}{:>4}{:<16}{:<}\n", "", std::get<0>(flag) + ",", "", std::get<1>(flag), std::get<2>(flag));
      // > Right Align  , Pad Left 8    , ""
      // < Left Align   , Pad Right 4   , "-h,"
      // > Right Align  , Pad Left 4    , ""
      // < Left Align   , Pad Right 16   , "--help"
      // < Left Align   ,               , "Show this help message"
    } else
      // > Right Align  , Pad Left 8    , ""
      // < Left Align   , Pad Right 24  , "-h,"
      // < Right Align   ,              , "Show this help message"
      fmt::print(stderr, 
          "{:>8}{:<24}{:>}\n", "", std::get<0>(flag) + ",", std::get<2>(flag));
  } 
}

void showUsage(std::string programName) { 
  fmt::print(stderr, "Usage: {} [embed/extract] -a [audio] -t [soundtag] -i [image]\n", programName);
  fmt::print(stderr, "Options:\n\n");
  std::map<int, std::tuple<std::string, std::string, std::string>> flags = {
    { 0, std::make_tuple("-h"     , "--help"        , "Show this help message")},
    { 1, std::make_tuple("-v"     , "--verbose"     , "Display program output and debugging information")},
    { 2, std::make_tuple("-a"     , ""              , "The file path to the audio file")},
    { 3, std::make_tuple("-i"     , ""              , "The file path to the image file")},
    { 4, std::make_tuple("-t"     , ""              , "The caption or tag for the audio file")},
    { 5, std::make_tuple("-r"     , "--readable"    , "Display file sizes in human readable numbers")},
    { 6, std::make_tuple("-si"    , ""              , "Show file sizes in MB")},
    { 7, std::make_tuple("-bin"   , ""              , "Show file sizes in MiB")}
  };

  std::map<int, std::tuple<std::string, std::string, std::string>> embedFlags = {
    { 0, std::make_tuple("embed"  , ""              , "Embed an audio file")},
    { 1, std::make_tuple("-f"     , "--fast"        , "Enable Mono Audio Channel encoding")},
    { 2, std::make_tuple("--ig"   , "--ignore-limit", "Allows you to encode files greater than 4 MiB")},
    { 3, std::make_tuple("-d"     , "--dest"        , "Change the output file name")},
  };

  std::map<int, std::tuple<std::string, std::string, std::string>> extractFlags = {
    { 0, std::make_tuple("extract", ""              , "Extract audio from an image")},
    { 1, std::make_tuple("-ad"    , ""              , "Change the audio file output file name")},
    { 2, std::make_tuple("-id"    , ""              , "Change the image file output file name")},
  };
  
  formatPrintUsage(flags);
  fmt::print(stderr, "{:>4}{}:\n\n", "", "Embedding");
  formatPrintUsage(embedFlags);
  fmt::print(stderr, "{:>4}{}:\n\n", "", "Extracting");
  formatPrintUsage(extractFlags);
} 

bool isEmpty(std::string arg, std::string errorMsg) {
  if (arg.empty()) { 
    showUsage("embed");
    fmt::print(stderr, "{}\n", errorMsg);
    return true;
  }
  else
    return false;
} 
