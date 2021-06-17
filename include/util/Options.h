#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <utility>
#include <tuple>
#include <unordered_map>

class Options {
  private:

std::unordered_map<std::string, std::tuple<std::string, std::string, bool>> options = {
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
    bool isMonoEnabled()              { return std::get<2>(options["Mono"]); }
    bool ignoreLimitEnabled()         { return std::get<2>(options["IgnoreLimit"]); }
    bool showVerboseEnabled()         { return std::get<2>(options["Verbose"]); }
    bool getOutputFile()              { return std::get<2>(options["Output"]); }
    bool getAudioFile()               { return std::get<2>(options["AudioFile"]); }
    bool getImageFile()               { return std::get<2>(options["ImageFile"]); }

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

    std::unordered_map<std::string, std::tuple<std::string, std::string, bool>> getOptions() { return options; }
    void enable(std::string option, bool toggled) { std::get<2>(this->options[option]) = toggled; }
};
#endif

