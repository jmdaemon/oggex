#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include <cstdint>

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
  cerr << "Usage:" << programName << " [audio_file] [image_file]\n" 
       << "Options:\n"
       << "\t-h, --help\t\tShow this help message\n"
       << "\t-f, --fast\t\tLower image quality\n"
       << endl;
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

bool notCorrupted(fs::path filepath) {
	ifstream file(filepath, ifstream::in | ifstream::binary);
	if (!file.is_open()) {
		cerr << "Error: couldn't open \"" << filepath << "\"" << endl;
    return false;
	}
  return true;
}

bool isImage(string file) { return isFile(file, ValidImageFileExtensions); }
bool isAudio(string file) { return isFile(file, ValidAudioFileExtensions); }
bool isImage(fs::path filepath) { return isFile(filepath.string(), ValidImageFileExtensions); }
bool isAudio(fs::path filepath) { return isFile(filepath.string(), ValidAudioFileExtensions); }

bool imageUnder4MiB (uintmax_t imageFileSize) {
  uintmax_t maxImageFileSize = 1024 * 1024 * 4; // About 4MB or exactly 4MiB
  if (imageFileSize > maxImageFileSize) {
		cerr << "Image is too large to fit sounds." << endl;
		return false;
  } else
  return true;
}

bool imageNotCorrupted(fs::path filepath) {
  return notCorrupted(filepath);
} 

map<int, string> parseOptions(int argc, char** argv) {
  if (!meetsReq(argc, argv)) {
    throw std::exception();
  }

  fs::path imageFilePath;
  fs::path audioFilePath;

  for (int i = 0; i < argc; i++) {
    string arg = string(argv[i]);

    if (arg.compare("-h") || arg.compare("--help")) { showUsage(argv[0]); } 
    if (arg.compare("-f") || arg.compare("--fast")) { bestQuality = true; }
    if (isImage(arg)) { imageFilePath = argv[i]; }
    if (isAudio(arg)) { audioFilePath = argv[i]; }
  } 

  if (imageFilePath.empty() || audioFilePath.empty()) {
    throw std::exception();
  }

  map<int, string> result = {{0, imageFilePath}, {1, audioFilePath}};
  return result; 
}

void cleanTempFiles() {
  fs::path tempImageFile = "nul";
  fs::path tempAudioFile = "out.ogg";
  if (!tempImageFile.empty()) {
    remove(tempImageFile);
  }
  if (!tempAudioFile.empty()) {
    remove(tempAudioFile);
  }
}

//void formatAudioTags() {
//// Format sound tag
  //unsigned int maxTagLength = 100;

  //vector<size_t> soundSizes;
  //vector<string> soundTags;
  //vector<bool> canQualityGain;


  //// if filename == audio.ogg, soundtag == audio
  //soundTags.push_back(audioFilePath.stem());
  
  //for (unsigned int i = 0; i < sounds.size(); ++i) {

    //soundSizes.push_back(0);
    //canQualityGain.push_back(true);

    //int j = soundTags[i].length() - 1; // get the actual length of the soundtag

    //for (; j >= 0; --j) {
      //// escape soundtags with "\\"
      //if (soundTags[i][j] == '\\' || soundTags[i][j] == '/') break;
    //}

    //if (j >= 0) soundTags[i] = soundTags[i].substr(j + 1, soundTags[i].length() - (j + 1));

    //if (soundTags[i].length() > maxTagLength - 2) soundTags[i] = soundTags[i].substr(0, maxTagLength - 2);

    //soundTags[i].insert(0, "[");
    //soundTags[i] += "]";
  //}
//}

int getFile(int argc, char** argv) {
  map<int, string> mediaFiles;
  try {
    mediaFiles = parseOptions(argc, argv);
  } catch (const std::exception&) {
    return -1;
  }

  fs::path audioFilePath = mediaFiles[0];
  fs::path imageFilePath = mediaFiles[1];

  vector<int> sounds; 

  uintmax_t imageFileSize = file_size(imageFilePath);

  if (!imageUnder4MiB(imageFileSize) && !notCorrupted(imageFilePath)) {
    return -1;
  } 
  return 0;
}

