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

struct AudioData {
  int audioQuality;
  bool lowQuality;
  string soundTag;
  fs::path audioFile;
  fs::path tempAudioFile;
  fs::path tempLogFile;
};

struct ImageData {
};

string buildCommand(AudioData data) {
  string command;
  string setAudioChannel = "";
  if (data.lowQuality) { setAudioChannel = " -ac 1"; } 
  command = fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn acodec libvorbis -aq {} {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1",
      data.audioFile.string(),
      data.audioQuality,
      setAudioChannel,
      data.tempAudioFile.string(),
      data.tempLogFile.string()
      );
  return command;
}

string exec(const char* cmd, AudioData data) {
    array<char, 512> buffer;
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

string encodeAudio(AudioData data, ofstream& file) {
  string cmd = buildCommand(data);
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

//array<char, 512> hashFile(array<char, 512> buffer, size_t count) {
array<char, length> hashFile(array<char, 512> buffer, size_t count, int length) {
  unsigned long long unmaskState = 0;
  array<char, length> maskedBuffer;
  int mask;
  for (unsigned int i = 0; i < count; ++i) {
    unmaskState = (1664525 * unmaskState + 1013904223) & 0xFFFFFFFF;
    mask = (unmaskState >> 24) & 0xFF;
    unmaskState += static_cast<unsigned int>(static_cast<unsigned char>(buffer[i] ^ mask));
    maskedBuffer[i] = buffer[i] ^ mask;
  }
  return maskedBuffer;
} 

void encodeTo(ifstream& inputFile, ofstream& outputFile, array<char, 512> buffer) {
  ostringstream contents;
  contents << inputFile.rdbuf();
  contents.seekp(0, ios::end);
  int contentSize = contents.tellp();

  outputFile << contents.rdbuf();
  hashFile(buffer, contentSize); // Write the imageFileHash to new outputFile
} 

//array<char, 512> stringToBuffer(string str) {
  //array<char, 512> buffer; 
  //copy(begin(str), end(str), buffer.begin());
  //return buffer;
//}

array<char, length> stringToBuffer(string str, int length) {
  array<char, length> buffer; 
  copy(begin(str), end(str), buffer.begin());
  return buffer;
}

void encodeImage(fs::path imageFilePath, fs::path encodedAudioFilePath, array<char, 512> audioBuffer, string soundTag) { 
  fs::path outputFilename = fmt::format("{}-embed{}", imageFilePath.stem(), imageFilePath.extension()); 
  //fs::path tempAudioFile = "temp.ogg";

  ofstream outputFile(outputFilename, ifstream::out | ifstream::binary);
  ifstream imageFileData(imageFilePath.c_str(), ifstream::in | ifstream::binary);
  ifstream audioFileData(encodedAudioFilePath.c_str(), ifstream::in | ifstream::binary);
  //ifstream audioFileData(tempAudioFile.c_str(), ifstream::in | ifstream::binary);

  if (isCorrupted(imageFilePath, imageFileData) || isCorrupted(tempAudioFile, tempFileData)) { 
    // clean
    throw exception(); 
  }
  //array<char, 512> originalBuffer;
  //copy(begin(audioBuffer), end(audioBuffer), begin(originalBuffer));

  // Process:
  // 1.
  // - Read an ImageFile with a given path into memory.
  // - Write the ImageFile to a new file, outputFile.
  // - Read the outputFile again, and write the ImageFile hash from the ImageFile
  // - Close ImageFile

  // 2.
  // - Open the AudioFile that was encoded with ffmpeg
  // - Read the soundTag into memory, and mask the tag with the hash
  // - Write the hashed soundTag to the outputFile

  // 3.
  // Read the AudioFile into memory, and mask the audio with the hash
  // Write the hashed AudioFile to the outPut File
  // Close all

  // Read ImageFile, write ImageFileData to outputFile, write Image Hash to audioBuffer
  // Ideally:
  //array<char, 512> imageContentBuffer = stringToBuffer(fileToString(imageFileData));
  //hashFile(imageContentBuffer, imageContentBuffer.size()); // Write the imageFileHash to new outputFile

  outputFile << imageFileData.rdbuf();

  imageFileData.seekp(0, ios::end);
  int imageContentSize = imageFileData.tellp(); // get Length
  array<char, imageContentSize> imageContent = stringToBuffer(fileToString(imageFileData), imageContentSize);

  hashFile(imageContent, imageContent.size(), imageContentSize); 
  imageFileData.close();
  //outputFile << imageFileData.rdbuf(); 

  //hashFile(audioBuffer, imageContentSize);
  //imageFileData.close();
  //outputFile << contents.rdbuf();
  //hashFile(buffer, contentSize); 
  //encodeTo(imageFileData, outputFile, audioBuffer);

  // Hash the soundTag (key), and write the content to file
  // Ideally:
  //array<char, 512> soundTagBuffer = hashFile(stringToBuffer(soundTag), soundTag.length());
  //outputFile.write(soundTagBuffer, soundTagBuffer.length());
  array<char, 512> soundTagBuffer = hashFile(stringToBuffer(soundTag), soundTag.length(), 100);
  outputFile.write(soundTagBuffer, soundTagBuffer.length());

  // Read the soundTag, write to outputFile

  //hashFile();

  //ostringstream soundTagContents;
  //soundTagContents.str(soundTag);
  //int soundTagLength = soundTag.length();
  //stringToBuffer();

  //outputFile << soundTagContents.rdbuf();

  // Read AudioFile, write AudioFile to outputFile, write ImageHash
  ostringstream audioFileContents;
  audioFileContents << audioFileData.rdbuf();
  audioFileContents.seekp(0, ios::end);
  int audioContentSize = audioFileData.tellp();

  array<char, audioContentSize> audioFileBuffer = stringToBuffer(fileToString(audioFileData), audioContentSize); 
  hashFile(audioFileBuffer, audioFileBuffer.size(), audioContentSize);
  //array<char, audioContentSize> audioFileBuffer = hashFile(audioBuffer, audioFileContents.size(), audioContentSize);
  outputFile.write(audioFileBuffer, audioContentSize);
  //outputFile << audioFileData.rdbuf();

  tempFileData.close();
  outputFile.close();
}

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
  //fs::path tempAudioFile = "out.ogg";
  fs::path encodedAudioFile = "out.ogg";
  vector<string> tags = formatAudioTags(audioFilePath.stem());

  AudioData audioData = { 10, false, tags.at(0), audioFilePath, tempAudioFile, tempLogFile};
  encodeImage(imageFilePath, encodedAudioFile, stringToBuffer(encodeAudio(audioData, audioFile)), tags.at(0));

  return 0;
} 
