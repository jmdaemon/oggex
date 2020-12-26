#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>

#include <cstdint>

#include <fmt/core.h>
#include <fmt/printf.h>

#include "EmbedAudio.h"
#include "Image.h"
#include "Audio.h"
#include "Mask.h"

using namespace std;
namespace fs = std::filesystem;

static bool bestQuality = true;

bool fileExists(fs::path filepath) { 
  ifstream file(filepath, ifstream::in | ifstream::binary);
  if (!file.is_open()) {
    fmt::fprintf(std::cerr, "Error: couldn't open \"%s\"\n", filepath);
    file.close();
    return true; 
  } 
  file.close();
  return false; 
}

void cleanTempFiles(fs::path tempLogFile, fs::path tempAudioFile) {
  if (!tempLogFile.empty())   { remove(tempLogFile); }
  if (!tempAudioFile.empty()) { remove(tempAudioFile); }
}

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
  if (data.lowQuality) { setAudioChannel = " -ac 1"; } 
  command = fmt::format(cmd,
      data.audioFile.string(),
      data.audioQuality,
      setAudioChannel,
      data.tempAudioFile.string(),
      data.tempLogFile.string()
      );
  fmt::print("{}\n", command);
  return command;
}

string buildCommand(Audio::AudioData data) { return createCommand(data); }
string encodeAudio(Audio::AudioData data) {
  return createCommand(data, "ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1");
}

string exec(const char* cmd, Audio::AudioData data) {
  ifstream dataContents(data.audioFile, ifstream::in | ifstream::binary);
  vector<char> buffer(4096);

  unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) { 
    fmt::fprintf(cerr, "Error: could not execute ffmpeg");
    cleanTempFiles(data.tempLogFile, data.tempAudioFile);
    throw runtime_error("popen() failed!");
  } 

  string monoEncoding = "";
  if (data.lowQuality) { monoEncoding = "/mono"; }
  fmt::print("Encoding \"{}\" at quality = {} {}\n\n", data.audioFile, data.audioQuality, monoEncoding);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) { ; }
  dataContents.close();

  ifstream tempFile(data.tempAudioFile, ifstream::in | ifstream::binary);
  ostringstream tempContents;
  tempContents << tempFile.rdbuf();
  string filedata = tempContents.str();
  tempFile.close();
  return filedata;
}

string encodeAudioFile(Audio::AudioData data, fs::path audioFilePath, fs::path imageFilePath) {
  string cmd = encodeAudio(data);
  string cmdOutput = exec(cmd.c_str(), data);

  //uintmax_t maxFileSize = 1024 * 1024 * 4; 
  size_t maxFileSize = 1024 * 1024 * 4; 
  //uintmax_t tempFileSize = fs::file_size(data.tempAudioFile);
  //uintmax_t imageFileSize = fs::file_size(imageFilePath);
  size_t tempFileSize   = getFileSize(data.tempAudioFile);
  size_t imageFileSize  = getFileSize(imageFilePath);

  size_t soundTagSize = data.soundTag.size();
  //uintmax_t soundTagSize = data.soundTag.size();

  if (fileExists(data.audioFile) || (tempFileSize <= 0)) {
    fmt::fprintf(cerr, "Error: encoding failed\n");
    throw exception();
  } else 
    fmt::print("Encoding completed.\n\n");

  uintmax_t totalSize = tempFileSize + imageFileSize + soundTagSize;
  fmt::print("tempFileSize: {}\nimageFileSize: {}\nsoundTagSize: {}\n", tempFileSize, imageFileSize, soundTagSize);
  fmt::print("Total size: {}\n", totalSize);
  //if ((soundTagSize + tempFileSize + tempFileSize) > maxFileSize) {
  if (totalSize > maxFileSize) {
    if (data.audioQuality > 4) {
      data.audioQuality -= 6;
      fmt::print("Decreasing quality. Quality = {}\n", data.audioQuality);
      encodeAudioFile(data, audioFilePath, imageFilePath);
    }
    if (data.audioQuality <= 4 && data.audioQuality > 0) {
      data.audioQuality -= 1;
      data.lowQuality = true;
      fmt::print("Decreasing quality. Quality = {}\n", data.audioQuality);
      fmt::print("Setting -ac 1 option \n");
      encodeAudioFile(data, audioFilePath, imageFilePath);
    } else {
      fmt::print("Audio file too big, try running with -f or --fast\n");
      return "";
    }
  } else {
    fs::rename(data.tempAudioFile, "temp.ogg");
    data.tempAudioFile = "temp.ogg";
  }
  return cmdOutput;
}

fs::path createOutputFileName(fs::path imageFilePath) {
  string stem = imageFilePath.stem();
  string ext = imageFilePath.extension();
  fs::path outputFilename = stem + "-embed" + ext;
  return outputFilename;
}

void encodeImage(fs::path imageFilePath, string encodedAudio, string soundTag, fs::path encodedAudioFilePath) { 
  fs::path outputFilename = createOutputFileName(imageFilePath);

  if (fileExists(imageFilePath) || fileExists(encodedAudioFilePath)) { 
  fmt::fprintf(cerr, "Image or Audio file does not exist or is being blocked\n");
  // clean
  throw exception();
  }

  ofstream outputFile(outputFilename, ifstream::out | ifstream::binary);
  ifstream imageFileData(imageFilePath, ifstream::in | ifstream::binary);
  ifstream audioFileData(encodedAudioFilePath, ifstream::in | ifstream::binary);

  outputFile << imageFileData.rdbuf() << soundTag << encodedAudio;
  outputFile.close();
  imageFileData.close();
  audioFileData.close();
}

int embed(fs::path imageFilePath, fs::path audioFilePath, string soundTag, bool quality) {
  bestQuality = quality;
  if (!under4MiB(imageFilePath) 
      && fileExists(imageFilePath) 
      && fileExists(audioFilePath)) { 
    return -1; 
  } 
  Audio::AudioData audioData = Audio::AudioData(soundTag, audioFilePath);
  string encodedAudio = encodeAudioFile(audioData, audioFilePath, imageFilePath);
  if (encodedAudio.empty()) { return -1; }
  encodeImage(imageFilePath, encodedAudio, soundTag, "temp.ogg");

  return 0;
} 
