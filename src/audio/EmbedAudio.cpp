#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

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

string createCommand( Audio::AudioData data, 
    string cmd = "ffmpeg -y -nostdin -i \"{}\" -vn acodec libvorbis -aq {} {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1") {
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
  return command;
}

string buildCommand(Audio::AudioData data) { return createCommand(data); }
string encodeAudio(Audio::AudioData data) {
  return createCommand(data, "ffmpeg -y -nostdin -i \"{}\" -vn acodec libvorbis -ar 44100 -aq {} {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1");
}

string exec(const char* cmd, Audio::AudioData data) {
  ifstream dataContents(data.audioFile.c_str(), ifstream::in | ifstream::binary);
  const int dataSize = getFileSize(dataContents); 
  vector<char> buffer(dataSize);
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) { 
      fmt::fprintf(cerr, "Error: could not execute ffmpeg");
      cleanTempFiles(data.tempLogFile, data.tempAudioFile);
      throw std::runtime_error("popen() failed!");
    } 
    string monoEncoding = "";
    if (data.lowQuality) { monoEncoding = "/mono"; }
    fmt::print("Encoding \"{}\" at quality = {} {}", data.audioFile, data.audioQuality, monoEncoding);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

string encodeAudio(Audio::AudioData data, ofstream& file) {
  //string cmd = buildCommand(data);
  string cmd = encodeAudio(data);
  string cmdOutput = exec(cmd.c_str(), data);

  uintmax_t maxFileSize = 1024 * 1024 * 4; 
  uintmax_t tempFileSize = file_size(data.tempAudioFile);
  uintmax_t soundTagSize = static_cast<uintmax_t>(data.soundTag.size());

  if (isCorrupted(data.audioFile, file) || (tempFileSize <= 0)) {
    fmt::fprintf(cerr, "Error: encoding failed\n");
    throw exception();
  } else 
    fmt::print("Encoding completed.");
  file.close();

  if ((soundTagSize + tempFileSize) > maxFileSize) {
    data.audioQuality -= 2;
  }
  
  fs::rename(data.tempAudioFile, "temp.ogg");
  return cmdOutput;
}

void encodeImage(fs::path imageFilePath, fs::path encodedAudioFilePath, string encodedAudio, string soundTag) { 
  fs::path outputFilename = fmt::format("{}-embed{}", imageFilePath.stem(), imageFilePath.extension()); 

  ofstream outputFile(outputFilename, ifstream::out | ifstream::binary);
  ifstream imageFileData(imageFilePath.c_str(), ifstream::in | ifstream::binary);
  ifstream audioFileData(encodedAudioFilePath.c_str(), ifstream::in | ifstream::binary);

  if (isCorrupted(imageFilePath, imageFileData) || isCorrupted(encodedAudio, audioFileData)) { 
    // clean
    throw exception(); 
  }

  outputFile << imageFileData.rdbuf();
  outputFile.write(soundTag.c_str(), soundTag.length());
  outputFile.write(encodedAudio.c_str(), encodedAudio.length());
  outputFile.close();
  imageFileData.close();
  audioFileData.close();
}

//int embed(int argc, char** argv) {
int embed(fs::path audioFilePath, fs::path imageFilePath, bool quality) {
  bestQuality = quality;

  ifstream imageFile(imageFilePath, ifstream::in | ifstream::binary);
  ofstream audioFile(audioFilePath, ifstream::out | ifstream::binary);
  if (!Image::imageUnder4MiB(file_size(imageFilePath)) && !isCorrupted(imageFilePath, imageFile) && !isCorrupted(audioFilePath, audioFile)) { 
    imageFile.close(); 
    audioFile.close();
    return -1; 
  } 
  fs::path tempLogFile = "Log.txt";
  fs::path encodedAudioFile = "out.ogg";
  vector<string> tags = formatAudioTags(audioFilePath.stem());

  Audio::AudioData audioData = { 10, false, tags.at(0), audioFilePath, encodedAudioFile, tempLogFile};
  encodeImage(imageFilePath, encodedAudioFile, encodeAudio(audioData, audioFile), tags.at(0));

  return 0;
} 
