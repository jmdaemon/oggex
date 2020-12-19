#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

#include <cstdint>
#include <cinttypes>

#include <fmt/core.h>
#include <fmt/printf.h>

#include "EmbedAudio.h"

using namespace std;
namespace fs = std::filesystem;

static bool bestQuality = true;
const static map<int, string> ValidImageFileExtensions = {
  {0, ".jpg"},
  {1, ".jpeg"},
  {2, ".gif"},
  {3, ".png"},
  {4, ".webm"},
};

const static map<int, string> ValidAudioFileExtensions = {
  {0, ".ogg"},
};

string toLowerCase(const fs::path& filePath) {
  string fpath = filePath.string();
  transform(fpath.begin(), fpath.end(), fpath.begin(), 
      [](unsigned char c ) { return tolower(c); }); 
  return fpath;
}

void showUsage(std::string programName) { 
  fmt::fprintf(cerr, 
      "Usage: %s [audio_file] [image_file]\n %s %s %s", programName, 
      "Options:\n", 
      "\t-h, --help\t\tShow this help message\n", 
      "\t-f, --fast\t\tLower image quality\n");
} 

bool meetsReq(int argc, char** argv) {
  if (argc <= 1 || !(argc > 1 && argc < 3)) {
    showUsage(argv[0]);
    throw std::exception();
  } 
  return true;
}

string getFileExtension(string file) {
  return (fs::path (file)).extension();
}

bool isFile(string file, const map<int, string> FileExtensions) {
  string extension = toLowerCase(getFileExtension(file));
  for (int i = 0; i < FileExtensions.size(); i++) {
    if(FileExtensions.at(i) == extension) {
      return true;
    }
  }
  return false;
}

bool fileUnder4MiB (uintmax_t fileSize, string errorMsg = "File too large to fit sounds.") {
  uintmax_t maxFileSize = 1024 * 1024 * 4; // About 4MB or exactly 4MiB
  if (fileSize > maxFileSize) {
		cerr << errorMsg << endl;
		return false;
  } else
  return true;
}

bool isImage(string file) { return isFile(file, ValidImageFileExtensions); }
bool isAudio(string file) { return isFile(file, ValidAudioFileExtensions); }
bool isImage(fs::path filepath) { return isFile(filepath.string(), ValidImageFileExtensions); }
bool isAudio(fs::path filepath) { return isFile(filepath.string(), ValidAudioFileExtensions); }

bool imageUnder4MiB (uintmax_t imageFileSize) {
  return fileUnder4MiB(imageFileSize, "Image is too large to fit sounds.");
}

map<int, string> parseOptions(int argc, char** argv) {
  if (!meetsReq(argc, argv)) { throw std::exception(); }

  fs::path imageFilePath;
  fs::path audioFilePath;

  for (int i = 0; i < argc; i++) {
    string arg = string(argv[i]);

    if (arg.compare("-h") || arg.compare("--help")) { showUsage(argv[0]); } 
    if (arg.compare("-f") || arg.compare("--fast")) { bestQuality = true; }
    if (isImage(arg)) { imageFilePath = argv[i]; }
    if (isAudio(arg)) { audioFilePath = argv[i]; }
  } 

  if (imageFilePath.empty() || audioFilePath.empty()) { throw std::exception(); }

  map<int, string> result = {{0, imageFilePath}, {1, audioFilePath}};
  return result; 
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

struct Data {
  int audioQuality;
  bool lowQuality;
  string soundTag;
  fs::path audioFile;
  fs::path tempAudioFile;
  fs::path tempLogFile;
};

string buildCommand(Data audioData) {
  string command;
  string setAudioChannel = "";
  if (audioData.lowQuality) { setAudioChannel = " -ac 1"; } 
  command = fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn acodec libvorbis -aq {} {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1",
      audioData.audioFile.string(),
      audioData.audioQuality,
      setAudioChannel,
      audioData.tempAudioFile.string(),
      audioData.tempLogFile.string()
      );
  return command;
}

string exec(const char* cmd, Data audioData) {
    array<char, 512> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) { 
      fmt::fprintf(cerr, "Error: could not execute ffmpeg");
      cleanTempFiles(audioData.tempLogFile, audioData.tempAudioFile);
      throw std::runtime_error("popen() failed!");
    } 
    string monoEncoding = "";
    if (audioData.lowQuality) { monoEncoding = "/mono"; }
    fmt::print("Encoding \"{}\" at quality = {} {}", audioData.audioFile, audioData.audioQuality, monoEncoding);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void encodeAudio(Data audioData, ofstream& file) {
  string cmd = buildCommand(audioData);
  string cmdOutput = exec(cmd.c_str(), audioData);

  uintmax_t maxFileSize = 1024 * 1024 * 4; 
  uintmax_t tempFileSize = file_size(audioData.tempAudioFile);
  uintmax_t soundTagSize = static_cast<uintmax_t>(audioData.soundTag.size());

  if (isCorrupted(audioData.audioFile, file) || (tempFileSize <= 0)) {
    fmt::fprintf(cerr, "Error: encoding failed\n");
    throw exception();
  } else 
    fmt::print("Encoding completed.");
  file.close();

  if ((soundTagSize + tempFileSize) > maxFileSize) {
    audioData.audioQuality -= 2;
  }
  fs::rename(audioData.tempAudioFile, "temp.ogg");
}

//void hashFile(char[] buffer) {
  //unsigned long long unmaskState = 0;
  //int mask;
  //for (unsigned int i = 0; i < count; ++i) {
    //unmaskState = (1664525 * unmaskState + 1013904223) & 0xFFFFFFFF;
    //mask = (unmaskState >> 24) & 0xFF;
    //unmaskState += static_cast<unsigned int>(static_cast<unsigned char>(buffer[i] ^ mask));
    //soundTags[j][i] = (soundTags[j][i] ^ mask);
  //}
//} 

//void hashAndWrite(char[] buffer) {
  //unsigned long long unmaskState = 0;
  //int mask;
  //for (unsigned int i = 0; i < buffer.length(); ++i) {
    //unmaskState = (1664525 * unmaskState + 1013904223) & 0xFFFFFFFF;
    //mask = (unmaskState >> 24) & 0xFF;
    ////unmaskState += static_cast<unsigned int>(static_cast<unsigned char>(soundTags[j][i]));
    //unmaskState += static_cast<unsigned int>(static_cast<unsigned char>(soundTags[j][i]));
    //soundTags[j][i] = (soundTags[j][i] ^ mask);
  //}
//}

//void writeMask(fs::path filepath, char[] buffer) {
  //ifstream f(filepath, ifstream::in | ifstream::binary);

  //while ((count = f.readsome(buffer, sizeof(buffer))) > 0) {
    //out.write(buffer, count);
    //hashFile(buffer);
  //} 
  //f.close();
//}




//void encodeImage(string imageFilePath, char[] buffer, string soundTag) { 
  //fs::path outputFilename = imageFilePath.stem() + "-embed" + imageFilePath.extension(); 
  //fs::path tempAudioFile = "temp.ogg"

  //if (isCorrupted(outputFilename) || (!notCorrupted(imageFilePath))) { 
      //throw exception(); 
  //} else if (notCorrupted(tempAudioFile)) { 
    //throw exception(); 
  //}
  //ofstream out(filepath, ifstream::out | ifstream::binary);
  //// soundTags[j][i] == 
  //// hashFile(soundTags[j][i]); // Get the soundtag
  ////out.write(soundTags[j].c_str(), soundTags[j].length()); // Write the sound tag to the buffer
  //hashFile(buffer);
  //hashAndWrite(soundTag);
  //hashAndWrite(buffer);

  //out.write(buffer, count);
  //f.close();
  //out.close();

	//// Remove temp files
	//clean(&tempAudioFile, &sounds);
//}

int embed(int argc, char** argv) {
  map<int, string> mediaFiles;
  try {
    mediaFiles = parseOptions(argc, argv);
  } catch (const std::exception&) {
    return -1;
  }

  fs::path audioFilePath = mediaFiles[0];
  fs::path imageFilePath = mediaFiles[1];

  ifstream imageFile(imageFilePath, ifstream::in | ifstream::binary);
  ofstream audioFile(audioFilePath, ifstream::out | ifstream::binary);
  if (!imageUnder4MiB(file_size(imageFilePath)) && !isCorrupted(imageFilePath, imageFile) && !isCorrupted(audioFilePath, audioFile)) { 
    imageFile.close(); 
    audioFile.close();
    return -1; 
  } 
  fs::path tempLogFile = "Log.txt";
  fs::path tempAudioFile = "out.ogg";
  vector<string> tags = formatAudioTags(audioFilePath.stem());

  Data audioData = { 10, false, tags.at(0), audioFilePath, tempAudioFile, tempLogFile};
  encodeAudio(audioData, audioFile);

  return 0;
} 
