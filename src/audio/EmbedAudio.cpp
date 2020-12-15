#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <tuple>
#include <filesystem> // C++17

#include <unistd.h>

using namespace std;
namespace fs = std::filesystem;

string getFileExtension(const fs::path& filePath) {
  return filePath.extension();
}


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

//tuple<fs::path, fs::path> mediaFiles;

tuple<fs::path, fs::path> parseOptions(int argc, char** argv) {
  if (argc <= 1) {
    showUsage(argv[0]);
    //return -1; 
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
    //mediaFiles{argv[optind], argv[optind + 1]};
    return tuple<fs::path, fs::path>{argv[optind], argv[optind + 1]};
    //return 0;
  }
}

const static map<int, string> ValidImageFileExtensions = {
  {0, ".jpg"},
  {1, ".jpeg"},
  {2, ".gif"},
  {3, ".png"},
  {4, ".webm"},
}

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
  size_t maxOutputSize = 1024 * 1024 * 4; 
  tuple<fs::path, fs::path> mediaFiles;
  try {
    mediaFiles = tuple<fs::path, fs::path> mediaFiles = parseOptions(argc, argv);
  } catch (const std::exception&) {
    return -1;
  }
  fs::path audioFilePath = get<0>(mediaFiles);
  fs::path imageFilePath = get(1)(mediaFiles);

  vector<int> sounds; 
  //int imageFile = -1;
  int imageFileExists = checkFile(imageFilePath);

  for (int i = 1; i < argc; ++i) { 
      sounds.push_back(i);
  }

  // Errors
  if (sounds.size() <= 0) {
    cerr << "Error: no sounds detected." << endl;
    return -1;
  }
  if (imageFile < 0) {
    cerr << "Error: no image detected." << endl;
    return -1;
  }
  return 0;
}

//int main(int argv, char** argv) {

//}


