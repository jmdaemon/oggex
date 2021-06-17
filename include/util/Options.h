#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

class Options {
  private:
    bool enableMonoAudio{};
    bool ignoreSizeLimit{};
    bool showDebugInfo{};
    bool setOutputFilename{};
    bool setAudioFilename{};
    bool setImageFilename{};

    std::string outputFile{};
    std::string audioFile{};
    std::string imageFile{};

  public:
    // Getters
    bool isMonoEnabled()            { return enableMonoAudio; }
    bool ignoreLimitEnabled()       { return ignoreSizeLimit; }
    bool showVerboseEnabled()       { return showDebugInfo; }
    bool getOutputFile()            { return setOutputFilename; }
    bool getAudioFile()             { return setAudioFilename; }
    bool getImageFile()             { return setImageFilename; }

    // Setters
    void enableMono(bool toggled)     { enableMonoAudio = toggled; }
    void ignoreLimit(bool toggled)    { ignoreSizeLimit = toggled; }
    void showVerbose(bool toggled)    { showDebugInfo = toggled; }  
    void setOutputFile(bool toggled)  { setOutputFilename = toggled; }
    void setAudioFile(bool toggled)   { setAudioFilename = toggled; }
    void setImageFile(bool toggled)   { setImageFilename = toggled; }  
};

#endif

