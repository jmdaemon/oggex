#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <utility>
#include <tuple>
#include <unordered_map>

typedef std::unordered_map<std::string, std::tuple<std::string, std::string, bool>> OptionsList;
class Options {
  private: 
    OptionsList options = {
      {"Mono"       ,   std::make_tuple("-f",  "--fast"         , false)}, 
      {"IgnoreLimit",   std::make_tuple("ig",  "--ignore-limit" , false)},
      {"Verbose"    ,   std::make_tuple("-v",  "--verbose"      , false)},
      {"Output"     ,   std::make_tuple("-d",  "--dest"         , false)},
      {"AudioFile"  ,   std::make_tuple("-ad", ""               , false)},
      {"ImageFile"  ,   std::make_tuple("-id", ""               , false)}
    };

    std::string outputFile;
    std::string audioFile;
    std::string imageFile;

  public:
    // Getters
    bool isMonoEnabled()              { return getOption("Mono"); }
    bool ignoreLimitEnabled()         { return getOption("IgnoreLimit"); }
    bool showVerboseEnabled()         { return getOption("Verbose"); }
    bool getOutputFile()              { return getOption("Output"); }
    bool getAudioFile()               { return getOption("AudioFile"); }
    bool getImageFile()               { return getOption("ImageFile"); }

    // Setters
    void enableMono(bool toggled)     { enable("Mono", toggled); }
    void ignoreLimit(bool toggled)    { enable("IgnoreLimit", toggled); }
    void showVerbose(bool toggled)    { enable("Verbose", toggled); }  
    void setOutputFile(bool toggled)  { enable("Output", toggled); }
    void setAudioFile(bool toggled)   { enable("AudioFile", toggled); }
    void setImageFile(bool toggled)   { enable("ImageFile", toggled); }  

    void setOutput(std::string filename)  { outputFile = filename; }
    void setAudio(std::string filename)  { audioFile = filename; }
    void setImage(std::string filename)  { imageFile = filename; } 

    OptionsList getOptions() { return options; }
    bool getOption(std::string option) { return std::get<2>(options[option]); }
    void enable(std::string option, bool toggled) { std::get<2>(this->options[option]) = toggled; }
};
#endif
