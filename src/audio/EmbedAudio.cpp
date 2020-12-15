#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <tuple>
#include <filesystem>
#include <cstdint>

#include <unistd.h>

using namespace std;
namespace fs = std::filesystem;

string toLowerCase(const fs::path& filePath) {
  string filePath = filePath.string();

  transform(filePath.begin(), filePath.end(), data.begin(),
      [](unsigned char c ) { return tolower(c); }); 
}

static void showUsage(std::string programName) { 
  cerr << "Usage:" << argv[0] << " [audio_file] [image_file]\n"; 
       << "Options:\n";
       << "\t-h, --help\t\tShow this help message\n";
       << "\t-f, --fast\t\tLower image quality\n";
       << endl;
}

static bool bestQuality = true;
const static struct option runtimeOptions [] = {
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
    break;

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
    auto imageFilePath = argv[optind];
    auto audioFilePath = argv[optind + 1];
    if (!imageFilePath.empty() && audioFilePath.empty()) {
      return tuple<fs::path, fs::path>{imageFilePath, audioFilePath};
    }
  }
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
    if(ValidImageFileExtensions[i] == extension) {
      fileExists++;
      break;
    }
  }
  return fileExists;
}


int getFiles(int argc, char** argv) {
  size_t maxOutputSize = 1024 * 1024 * 4; // About 4MB or exactly 4MiB
  uintmax_t maxImageFileSize = 1024 * 1024 * 4; // About 4MB or exactly 4MiB
  tuple<fs::path, fs::path> mediaFiles;
  try {
    mediaFiles = tuple<fs::path, fs::path> mediaFiles = parseOptions(argc, argv);
  } catch (const std::exception&) {
    return -1;
  }
  fs::path audioFilePath = get<0>(mediaFiles);
  fs::path imageFilePath = get(1)(mediaFiles);

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

  uintmax_t maxImageFileSize = 1024 * 1024 * 4;
  uintmax_t imageFileSize = file_size(imageFilePath);

  if (imageFileSize > maxImageFileSize) {
		cerr << "Image is too large to fit sounds." << endl;
		return 0;
  }

	ifstream imageFile(imageFilePath, ifstream::in | ifstream::binary);
	if (!imageFile.is_open()) {
		cerr << "Error: couldn't open \"" << imageFilePath << "\"" << endl;
		return -1;
	}

	//f.seekg(0, ifstream::end);
	//size_t imageSize = f.tellg();
	//f.close();

	//// Temp file removal
	//string tempLogFile = "nul";
	//string tempAudioFile = "out.ogg";
	//f.open(tempAudioFile.c_str(), ifstream::in | ifstream::binary);
	//if (f.is_open()) {
		//f.close();
		//remove(tempAudioFile.c_str());
	//}
  return 0;

}

