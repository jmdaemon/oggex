#pragma once
#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <tuple>
#include <unordered_map>

typedef std::unordered_map<std::string, std::tuple<std::string, std::string, bool>> OptionsList;
class Options {
  private: 
    OptionsList options = {
      {"Mono"           ,   std::make_tuple("-f"  , "--fast"          , false)}, 
      {"IgnoreLimit"    ,   std::make_tuple("ig"  , "--ignore-limit"  , false)},
      {"Verbose"        ,   std::make_tuple("-v"  , "--verbose"       , false)},
      {"Output"         ,   std::make_tuple("-d"  , "--dest"          , false)},
      {"AudioFile"      ,   std::make_tuple("-ad" , ""                , false)},
      {"ImageFile"      ,   std::make_tuple("-id" , ""                , false)},
      {"HumanReadable"  ,   std::make_tuple("-r"  , "--readable"      , false)},
      {"ShowSIUnits"    ,   std::make_tuple("-si" , ""                , false)}
    };

    std::unordered_map<std::string, std::string> outputFiles = {
      {"OutputFile" , ""},
      {"AudioFile"  , ""},
      {"ImageFile"  , ""}
    };

  public:
    // Getters
    bool isMonoEnabled()                  { return isEnabled("Mono"); }
    bool isReadableEnabled()              { return isEnabled("HumanReadable"); }
    bool isSIEnabled()                    { return isEnabled("ShowSIUnits"); }
    bool ignoreLimitEnabled()             { return isEnabled("IgnoreLimit"); }
    bool showVerboseEnabled()             { return isEnabled("Verbose"); }
    bool outputFileEnabled()              { return isEnabled("Output"); }
    bool audioFileEnabled()               { return isEnabled("AudioFile"); }
    bool imageFileEnabled()               { return isEnabled("ImageFile"); }
    std::string getOutputFile()           { return getFileName("OutputFile"); }
    std::string getAudioFile()            { return getFileName("AudioFile"); }
    std::string getImageFile()            { return getFileName("ImageFile"); }

    // Setters
    void enableMono(bool toggled)         { enable("Mono", toggled); }
    void ignoreLimit(bool toggled)        { enable("IgnoreLimit", toggled); }
    void showVerbose(bool toggled)        { enable("Verbose", toggled); }  
    void setOutputFile(bool toggled)      { enable("Output", toggled); }
    void setAudioFile(bool toggled)       { enable("AudioFile", toggled); }
    void setImageFile(bool toggled)       { enable("ImageFile", toggled); }  

    void setOutput(std::string filename)  { setFileName("OutputFile", filename); }
    void setAudio(std::string filename)   { setFileName("AudioFile", filename); }
    void setImage(std::string filename)   { setFileName("ImageFile", filename); } 

    // options
    OptionsList getOptions()                                  { return options; }
    bool isEnabled(std::string option)                        { return std::get<2>(options[option]); }
    void enable(std::string option, bool toggled)             { std::get<2>(this->options[option]) = toggled; }

    // outputFiles
    std::string getFileName(std::string file)                 { return outputFiles[file]; }
    void setFileName(std::string file, std::string filename)  { outputFiles[file] = filename; }
};
#endif
