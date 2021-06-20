#include "Cmd.h"

#include <map>
#include <tuple>

void showUsage(std::string programName) { 
  fmt::print(stderr, "Usage: {} [embed/extract] -a [audio] -t [soundtag] -i [image]\n", programName);
  fmt::print(stderr, "Options:\n\n");
  std::map<int, std::tuple<std::string, std::string, std::string>> flags = {
    { 0, std::make_tuple("-h"   , "--help"      , "Show this help message")},
    { 1, std::make_tuple("-v"   , "--verbose"   , "Display program output and debugging information")},
    { 2, std::make_tuple("-a"   , ""            , "The file path to the audio file")},
    { 3, std::make_tuple("-i"   , ""            , "The file path to the image file")},
    { 4, std::make_tuple("-t"   , ""            , "The caption or tag for the audio file")},
    { 5, std::make_tuple("-r"   , "--readable"  , "Display file sizes in human readable numbers")},
    { 6, std::make_tuple("-si"  , ""            , "Show file sizes in MB")},
    { 7, std::make_tuple("-bin" , ""            , "Show file sizes in MiB")}
  };

  for (auto const& [key, flag] : flags) { 
    if (!std::get<1>(flag).empty()) {
      //fmt::print(stderr, "{:<8}{}, {:<4}{:^16}{}\n", "", std::get<0>(flag), std::get<1>(flag), "", std::get<2>(flag));
      //fmt::print(stderr, "{:<8}{},{:<4}{:^16}{}\n", "", std::get<0>(flag), std::get<1>(flag), "", std::get<2>(flag));
      fmt::print(stderr, 
          //"{:>8}{:<4}{:>4}{:<8}{:>8}{:<}\n", "", std::get<0>(flag) + ",", "", std::get<1>(flag), std::get<2>(flag));
          //"{:>8}{:<4}{:>4}{:<4}{:>4}{:<}\n", "", std::get<0>(flag) + ",", "", std::get<1>(flag), "", std::get<2>(flag));
          "{:>8}{:<4}{:>4}{:<16}{:<}\n", "", std::get<0>(flag) + ",", "", std::get<1>(flag), std::get<2>(flag));
      // > Right Align  , Pad Left 8    , ""
      // < Left Align   , Pad Right 4   , "-h,"
      // > Right Align  , Pad Left 4    , ""
      // < Left Align   , Pad Right 16   , "--help"
      // < Left Align   ,               , "Show this help message"

        //"{:>8}{:<8}{:<8}{:<}\n", "", std::get<0>(flag) + ",", std::get<1>(flag), std::get<2>(flag));
      // Right Align  , Pad Left 8    , ""
      // Left Align   , Pad Right 8   , "-h,"
      // Left Align   , Pad Right 8   , "--help"
      // Left Align   ,               , "Show this help message"
    } else
      // > Right Align  , Pad Left 8    , ""
      // < Left Align   , Pad Right 4   , "-h,"
      // > Right Align  , Pad Left 4    , ""
      // < Left Align   , Pad Right 16   , ""
      // < Left Align   ,               , "Show this help message"

      
      /// V2
      // > Right Align  , Pad Left 8    , ""
      // < Left Align   , Pad Right 4   , "-h,"
      //// > Right Align  , Pad Left 20    , ""
      //// < Left Align   , Pad Right 16   , ""
      // < Left Align   ,               , "Show this help message"
      fmt::print(stderr, 
          //"{:>8}{:<4}{:>4}{:<16}{:<}\n", "", std::get<0>(flag) + ",", "", "", std::get<2>(flag));
          "{:>8}{:<24}{:>}\n", "", std::get<0>(flag) + ",", std::get<2>(flag));
      // Padding in front
      // Left Align -> Pad Right 4
      // Right Align -> Pad Left 8
      // Left Align
      //fmt::print(stderr, 
          //"{:>8}{:<4}{:>4} {:>8}{:<}\n", "", std::get<0>(flag) + ",", "", "", std::get<2>(flag));
      //fmt::print(stderr, "{:<8}{}  {:20}{}\n", "", std::get<0>(flag), "", std::get<2>(flag));
      //fmt::print(stderr, "{:<8}{}  {:20}{}\n", "", std::get<0>(flag), "", std::get<2>(flag));
      //fmt::print(stderr, "{:<8}{}  {:<4}{:^16}{}\n", "", std::get<0>(flag), "", std::get<2>(flag));

  }

  //fmt::print(stderr, 
      //"{:<8},\n{1}\n{2}\n{3}\n{4}\n{5}\n{6}\n{7}\n\n", 
        //"-h,  \t--help\t\tShow this help message",
        //"-v,  \t--verbose\tDisplay program output and debugging information",
        //"-a,  \t\t\tThe file path to the audio file",
        //"-i,  \t\t\tThe file path to the image file",
        //"-t,  \t\t\tThe caption or tag for the audio file",
        //"-r, \t--readable\tDisplay file sizes in human readable numbers",
        //"-si, \t\t\tDisplay file sizes using MB units",
        //"-bin, \t\t\tDisplay file sizes using MiB units"
      //);
  fmt::print(stderr, 
      "{:>4}\n{}\n{}\n{}\n{}\n\n{:>4}\n{}\n{}\n{}\n \n\n", 
        "    Embedding:", 
              "\tembed, \t-m\t\tEmbed an audio file", 
              "\t-f,  \t--fast\t\tEnable Mono Audio Channel encoding",
              "\t-ig, \t--ignore-limit\tAllows you to encode files greater than 4 MiB", 
              "\t-d,  \t--dest \t\tChange the output file name.",
        "    Encoding:", 
              "\textract, -x\t\tExtract audio from an image",
              "\t-ad, \t\t\tChange the audio file output file name.",
              "\t-id, \t\t\tChange the image file output file name."
      );
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
