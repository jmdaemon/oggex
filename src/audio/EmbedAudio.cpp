#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

//#include <fmt/core.h>
//#include <fmt/printf.h>
//#include <fmt/format.h>

#include "EmbedAudio.h"
#include "Image.h"
#include "Audio.h"
#include "Mask.h"

using namespace std;
namespace fs = std::filesystem;

static bool bestQuality = true;

bool tagUnder100(unsigned int tagLength) {
  unsigned int maxTagLength = 100;
  if (tagLength < maxTagLength) {
    return true;
  }
  return false;
}

vector<string> formatAudioTags(string tag) {
  vector<string> soundTags;
  string soundTag = "[" + tag + "]";
  soundTags.push_back(soundTag); // audio.ogg ==> [audio] 
  return soundTags;
}

string createCommand(Audio::AudioData data, string cmd) {
  string command;
  string setAudioChannel = "";
  if (data.getEncodingQuality()) { setAudioChannel = " -ac 1"; } 
  //command = fmt::format(cmd,
      //data.getAudio().string(),
      //data.getAudioQuality(),
      //setAudioChannel,
      //data.getTempAudio().string(),
      //data.getTempLog().string()
      //);
  command = "NA";
  fmt::print("{}\n", command);
  return command;
}

string buildCommand(Audio::AudioData data) { return createCommand(data); }
string encodeAudio(Audio::AudioData data) {
  return createCommand(data, 
      "ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1");
}

string exec(const char* cmd, Audio::AudioData data) {
  ifstream dataContents(data.getAudio(), ifstream::in | ifstream::binary);
  vector<char> buffer(4096);

  unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) { 
    //fmt::fprintf(cerr, "Error: could not execute ffmpeg");
    clean({ data.getTempLog(), data.getTempAudio()});
    throw runtime_error("popen() failed!");
  } 

  string monoEncoding = "";
  if (data.getEncodingQuality()) { monoEncoding = "/mono"; }
  //fmt::print("Encoding \"{}\" at quality = {} {}\n\n", data.getAudio(), data.getAudioQuality(), monoEncoding);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) { ; }
  dataContents.close();

  ifstream tempFile(data.getTempAudio(), ifstream::in | ifstream::binary);
  string filedata = dataToString(tempFile);
  tempFile.close();
  return filedata;
}

void decreaseQuality(unsigned int subtrahend, Audio::AudioData& data) {
  data.setAudioQuality(data.getAudioQuality() - subtrahend);
  fmt::print("Decreasing quality. Quality = {}\n", data.getAudioQuality());
}

uintmax_t calculateTotalSize(Audio::AudioData data, fs::path imageFilePath, size_t maxFileSize = 1024 * 1024 * 4) {
  size_t tempFileSize   = getFileSize(data.getTempAudio());
  size_t imageFileSize  = getFileSize(imageFilePath);
  size_t soundTagSize   = data.getSoundTag().size();
  uintmax_t totalSize   = tempFileSize + imageFileSize + soundTagSize;

  if (!fileExists(data.getAudio()) || (tempFileSize <= 0)) {
    //fmt::fprintf(cerr, "Error: encoding failed\n");
    throw exception();
  } else 
    fmt::print("Encoding completed.\n\n");

  fmt::print("File Sizes: \n==========\n");
  fmt::print("Max File Size: {}\nTemp File Size: {}\nImage File Size: {}\nSound Tag Size: {}\n", maxFileSize, tempFileSize, imageFileSize, soundTagSize);
  fmt::print("Total size: {}\n", totalSize);

  return totalSize;
}

string encodeAudioFile(Audio::AudioData& data, fs::path imageFilePath) {
  string cmdOutput = exec(encodeAudio(data).c_str(), data);
  size_t maxFileSize    = 1024 * 1024 * 4; 
  uintmax_t totalSize   = calculateTotalSize(data, imageFilePath);
  if (totalSize > maxFileSize) {
    if (data.getAudioQuality() == 10) {
      decreaseQuality(6, data);
      encodeAudioFile(data, imageFilePath);
    } else if (data.getAudioQuality() <= 4 && data.getAudioQuality() > 0) {
      decreaseQuality(1, data);
      data.setEncodingQuality(true);
      fmt::print("Setting -ac 1 option \n");
      encodeAudioFile(data, imageFilePath);
    } else {
      fmt::print("Audio file too big, try running with -f or --fast\n");
      throw exception();
    }
  } else {
    fs::rename(data.getTempAudio(), "temp.ogg");
    data.getTempAudio() = "temp.ogg";
  }
  return cmdOutput;
}

fs::path createOutputFileName(fs::path imageFilePath) {
  string stem = imageFilePath.stem();
  string ext = imageFilePath.extension();
  fs::path outputFilename = stem + "-embed" + ext;
  return outputFilename;
}

void encodeImage(fs::path imageFilePath, string soundTag, fs::path encodedAudioFilePath) { 
  fs::path outputFilename = createOutputFileName(imageFilePath);
  if (!fileExists(encodedAudioFilePath)) { 
    //fmt::fprintf(cerr, "Image or Audio file does not exist or is being blocked\n");
    clean({imageFilePath, encodedAudioFilePath});
    throw exception();
  }

  ofstream outputFile(outputFilename, ifstream::out | ifstream::binary);
  ifstream imageFileData(imageFilePath, ifstream::in | ifstream::binary);
  ifstream audioFileData(encodedAudioFilePath, ifstream::in | ifstream::binary);

  outputFile << imageFileData.rdbuf() << soundTag << audioFileData.rdbuf();
  outputFile.close();
  imageFileData.close();
  audioFileData.close();
  clean({encodedAudioFilePath});
}

int embed(fs::path imageFilePath, fs::path audioFilePath, string soundTag, bool quality) {
  bestQuality = quality;
  if (!under4MiB(imageFilePath) || !fileExists(imageFilePath) || !fileExists(audioFilePath)) { return -1; } 
  //Audio::AudioData audioData = Audio::AudioData(soundTag, audioFilePath);
  Audio::AudioData audioData = createAudioData(soundTag, audioFilePath);
  encodeAudioFile(audioData, imageFilePath);
  encodeImage(imageFilePath, soundTag, audioData.getTempAudio());
  return 0;
} 
