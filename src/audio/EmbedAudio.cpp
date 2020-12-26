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
      data.audioFile,
      //data.audioFile.string(),
      data.audioQuality,
      setAudioChannel,
      data.tempAudioFile,
      //data.tempAudioFile.string(),
      //data.tempLogFile.string()
      data.tempLogFile
      );
  fmt::print("{}\n", command);
  return command;
}

string buildCommand(Audio::AudioData data) { return createCommand(data); }
string encodeAudio(Audio::AudioData data) {
  return createCommand(data, "ffmpeg -y -nostdin -i {} -vn -codec:a libvorbis -ar 44100 -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1");
  //return createCommand(data, "ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {} {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1");
}

string exec(const char* cmd, Audio::AudioData data) {

  //ifstream dataContents(data.audioFile.c_str(), ifstream::in | ifstream::binary);
  ifstream dataContents(data.audioFile, ifstream::in | ifstream::binary);
  //const size_t dataSize = getFileSize(dataContents); 
  //const size_t dataSize = getFileSize(dataContents); 
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

  // By this point, ffmpeg should have generated the needed out.ogg temp file
  ifstream tempFile(data.tempAudioFile, ifstream::in | ifstream::binary);
  ostringstream tempContents;
  tempContents << tempFile.rdbuf();
  string filedata = tempContents.str();
  return filedata;
}

//string encodeAudio(Audio::AudioData data, ofstream& file) {
//string encodeAudio(Audio::AudioData data, ifstream& file) {
string encodeAudioFile(Audio::AudioData data, fs::path filepath) {
  string cmd = encodeAudio(data);
  string cmdOutput = exec(cmd.c_str(), data);

  uintmax_t maxFileSize = 1024 * 1024 * 4; 
  uintmax_t tempFileSize = fs::file_size(data.tempAudioFile);
  uintmax_t soundTagSize = static_cast<uintmax_t>(data.soundTag.size());

  ifstream file(filepath, ifstream::in | ifstream::binary);
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
  data.tempAudioFile = "temp.ogg";
  return cmdOutput;
}

fs::path createOutputFileName(fs::path imageFilePath) {
  string stem = imageFilePath.stem();
  string ext = imageFilePath.extension();
  fs::path outputFilename = stem + "-embed" + ext;
  return outputFilename;
}

void encodeImage(fs::path imageFilePath, string encodedAudio, string soundTag, fs::path encodedAudioFilePath) { 
  //fs::path outputFilename = imageFilePath + "embed" + ;
  fs::path outputFilename = createOutputFileName(imageFilePath);

  ofstream outputFile(outputFilename, ifstream::out | ifstream::binary);
  ifstream imageFileData(imageFilePath.c_str(), ifstream::in | ifstream::binary);
  ifstream audioFileData(encodedAudioFilePath.c_str(), ifstream::in | ifstream::binary);

  if (isCorrupted(imageFilePath, imageFileData) || isCorrupted(encodedAudio, audioFileData)) { 
    // clean
    throw exception(); 
  }

  outputFile << imageFileData.rdbuf() << soundTag << encodedAudio;
  outputFile.close();
  imageFileData.close();
  audioFileData.close();
}

int embed(fs::path imageFilePath, fs::path audioFilePath, string soundTag, bool quality) {
  bestQuality = quality;

  ifstream imageFile(imageFilePath, ifstream::in | ifstream::binary);
  ifstream audioFile(audioFilePath, ifstream::in | ifstream::binary);
  //ofstream audioFile(audioFilePath, ifstream::out | ifstream::binary);
  if (!Image::imageUnder4MiB(file_size(imageFilePath)) 
      && !isCorrupted(imageFilePath, imageFile) 
      && !isCorrupted(audioFilePath, audioFile)) { 
    imageFile.close(); 
    audioFile.close();
    return -1; 
  } 
  imageFile.close();
  audioFile.close();
  //vector<string> tags = formatAudioTags(audioFilePath.stem());

  //Audio::AudioData audioData = Audio::AudioData(tags.at(0), audioFilePath);
  //encodeImage(imageFilePath, encodeAudio(audioData, audioFile), tags.at(0));
  Audio::AudioData audioData = Audio::AudioData(soundTag, audioFilePath);
  //string encodedAudio = encodeAudioFile(audioData, audioFile);
  string encodedAudio = encodeAudioFile(audioData, audioFilePath);
  //encodeImage(imageFilePath, encodeAudio(audioData, audioFile), soundTag);
  encodeImage(imageFilePath, encodedAudio, soundTag);

  return 0;
} 
