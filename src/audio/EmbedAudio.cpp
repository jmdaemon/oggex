#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <tuple>
#include <filesystem>
#include <map>
#include <exception>

#include <cstdlib>
#include <cstdio>
#include <cstdint>

#include <unistd.h>
#include <getopt.h>

#include <EmbedAudio.h>

using namespace std;
namespace fs = std::filesystem;

string toLowerCase(const fs::path& filePath) {
  string fpath = filePath.string();
  transform(fpath.begin(), fpath.end(), fpath.begin(), 
      [](unsigned char c ) { return tolower(c); }); 
  return fpath;
}

static void showUsage(std::string programName) { 
  cerr << "Usage:" << programName << " [audio_file] [image_file]\n" 
       << "Options:\n"
       << "\t-h, --help\t\tShow this help message\n"
       << "\t-f, --fast\t\tLower image quality\n"
       << endl;
}

static bool bestQuality = true;
static struct option runtimeOptions [] = {
  {"help",  no_argument,    0, 'h'},
  {"fast",  no_argument,    0, 'f'},
  {0,0,0,0}, 
};

tuple<fs::path, fs::path> parseOptions(int argc, char** argv) {
  if (argc <= 1) {
    showUsage(argv[0]);
    throw std::exception();
  }

  int c;
  int option_index = 0; 

  c = getopt_long (argc, argv, "hf", runtimeOptions, &option_index);

  if (c == -1)
    throw std::exception();
    //break;

  switch(c) {
    case 'h':
      showUsage(argv[0]);
      break;
    case 'f': 
      bestQuality = true; 
      break; 
    case '?':
      showUsage(argv[0]);
      break;
    default: 
      abort();
  }

  if (optind < 2) {
    fs::path imageFilePath = argv[optind];
    fs::path audioFilePath = argv[optind + 1];
    if (!imageFilePath.empty() && audioFilePath.empty()) {
      return tuple<fs::path, fs::path>{imageFilePath, audioFilePath};
    }
  }
  return std::make_tuple("", "");
}

const static map<int, string> ValidImageFileExtensions = {
  {0, ".jpg"},
  {1, ".jpeg"},
  {2, ".gif"},
  {3, ".png"},
  {4, ".webm"},
};

int checkFile(fs::path filePath) {
  int fileExists = 0;
  string extension = toLowerCase(filePath.extension());
  for (int i = 0; i < 5; i++) {
    //if(ValidImageFileExtensions[i] == extension) {
    if(ValidImageFileExtensions.at(i) == extension) {
      fileExists++;
      break;
    }
  }
  return fileExists;
}

bool imageUnder4MiB (uintmax_t imageFileSize) {
  uintmax_t maxImageFileSize = 1024 * 1024 * 4; // About 4MB or exactly 4MiB
  if (imageFileSize > maxImageFileSize) {
		cerr << "Image is too large to fit sounds." << endl;
		return false;
  } else
  return true;
}

bool imageNotCorrupted(fs::path imageFilePath) {
	ifstream imageFile(imageFilePath, ifstream::in | ifstream::binary);
	if (!imageFile.is_open()) {
		cerr << "Error: couldn't open \"" << imageFilePath << "\"" << endl;
    return false;
	}
  return true;
}

void cleanTempFiles() {
  //Marker
  //// Clean up tempFiles
  //// Temp file removal
  ////string tempLogFile = "nul";
  ////string tempAudioFile = "out.ogg";
  //fs::path tempLogFile = "nul";
  //fs::path tempAudioFile = "out.ogg";
  ////f.open(tempAudioFile.c_str(), ifstream::in | ifstream::binary);
  //audioFile.open(tempAudioFile, ifstream::in | ifstream::binary);
  //if (audioFile.is_open()) {
    //audioFile.close();
    //remove(audioFile);
  //}
}


int getFile(int argc, char** argv) {
  tuple<fs::path, fs::path> mediaFiles;
  try {
    mediaFiles = parseOptions(argc, argv);
  } catch (const std::exception&) {
    return -1;
  }
  fs::path audioFilePath = get<0>(mediaFiles);
  fs::path imageFilePath = get<1>(mediaFiles);
  //fs::path audioFilePath = mediaFiles.get(0);
  //fs::path imageFilePath = mediaFiles.get(0);
  //fs::path audioFilePath = get<0>(mediaFiles);
  //fs::path imageFilePath = get(1)(mediaFiles);

  //fs::path audioFilePath, imageFilePath;
  //auto [audioFilePath, imageFilePath] = get<0>(mediaFiles);


  vector<int> sounds; 
  int imageFileExists = checkFile(imageFilePath);

  for (int i = 1; i < argc; ++i) { 
      sounds.push_back(i);
  }

  // Errors
  //if (sounds.size() <= 0) {
    //cerr << "Error: no sounds detected." << endl;
    //return -1;
  //}

  uintmax_t imageFileSize = file_size(imageFilePath);

  if (!imageUnder4MiB(imageFileSize) && !imageNotCorrupted(imageFilePath)) {
    return -1;
  } 

  

  //unsigned int maxTagLength = 100;
  //vector<size_t> soundSizes;
  //vector<string> soundTags;
  //vector<bool> canQualityGain;
  //for (unsigned int i = 0; i < sounds.size(); ++i) {

    //soundSizes.push_back(0);
    //canQualityGain.push_back(true);

    //soundTags.push_back(argv[sounds[i]]);
    //ext = getExtension(soundTags[i]);

    //soundTags[i] = soundTags[i].substr(0, soundTags[i].length() - ext.length());
    //int j = soundTags[i].length() - 1;

    //for (; j >= 0; --j) {
      //if (soundTags[i][j] == '\\' || soundTags[i][j] == '/') break;
    //}

    //if (j >= 0) soundTags[i] = soundTags[i].substr(j + 1, soundTags[i].length() - (j + 1));
    //if (soundTags[i].length() > maxTagLength - 2) soundTags[i] = soundTags[i].substr(0, maxTagLength - 2);
    //soundTags[i].insert(0, "[");
    //soundTags[i] += "]";
  //}
  return 0;
}

