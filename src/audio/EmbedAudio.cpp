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

//stringstream buildCommand(int quality, string audioFilePath) {
	//stringstream cmd;
  //cmd.str("");
  //cmd << "ffmpeg -y -nostdin -i \""
    //<< audioFilePath
    ////<< argv[sounds[i]]
    //<< "\" -vn"
    //<< " -acodec libvorbis -aq "
    //<< ((quality < 0) ? 0 : quality);
  //if (quality < 0) cmd << " -ac 1";
  //cmd << " -map_metadata -1 \""
    //<< tempAudioFile
    //<< "\" >> \""
    //<< tempLogFile
    //<< "\" 2>&1";
  //return cmd
  //}


//void encodeFile(string audioFilePath) {
	//char buffer[512];
	//bool qualityMinimized = false;
	//bool qualityIncreased = false;

  //uintmax_t audioFileSize = file_size(audioFilePath);
	//for (int quality = 0; quality <= 10; ++quality) {
		//unsigned int i;
		//unsigned int soundsFit = 0;
		//for (i = 0; i < sounds.size(); ++i) {
      //stringstream cmd = buildCommand(quality, audioFilePath);
      //fs::path tempAudioFile = "out.ogg";

			//// Execute
			//FILE* stream = popen(cmd.str().c_str(), "r");
			//if (stream == NULL) {
				//cerr << "Error: could not execute ffmpeg" << endl;
				//clean(&tempAudioFile, &sounds);
				//return -1;
			//}

			////cout << "Encoding \"" << argv[sounds[i]] << "\" @ quality=" << ((quality < 0) ? 0 : quality);
      //cout << "Encoding \"" << audioFilePath << "\" @ quality=" << ((quality < 0) ? 0 : quality);
			//if (quality < 0) cout << "/mono";
			//cout << "..." << endl;

			//while (fgets(buffer, sizeof(buffer), stream) != NULL); // Read and store in buffer
			//pclose(stream);

      //uintmax_t tempFileSize = file_size(tempAudioFile);

      //if (!notCorrupted(tempAudioFile)) {
				//cerr << "Error: encoding failed" << endl;
				//clean(&tempAudioFile, &sounds);
				//return -1;
      //} else if (tempFileSize <= 0) {
				//cout << "Encoding failed" << endl << endl;
      //} else 
        //cout << "Encoding completed" << endl;

      //if (tempAudioFile) {
      //}
				//// Check if fittable
				//size_t space = maxOutputSize - imageSize;
				//for (unsigned int j = 0; j < sounds.size(); ++j) {
					//assert(soundSizes[j] + soundTags[j].length() <= space);
					//space -= soundSizes[j] + soundTags[j].length();
				//}

				//// It doesn't...
				//if (fileSize + soundTags[i].length() > space) {
					//// Minimize quality (if the quality hasn't already been increased)
					//if (!qualityIncreased) {
						//if (!qualityMinimized) {
							//// Quality minimize
							//for (unsigned int j = 0; j < sounds.size(); ++j) {
								//soundSizes[j] = 0;
							//}
							//soundsFit = 0;
							//quality -= 2;
							//qualityMinimized = (quality < -1);
							//cout << "Quality decreased" << endl << endl;
							//break;
						//}
						//else {
							//// Can't fit
							//cout << "Warning: sound file \"" << argv[sounds[i]] << "\" cannot be fit." << endl;
						//}
					//}
				//}
				//// It does
				//else {
					//// Fit okay
					//soundSizes[i] = fileSize;
					//++soundsFit;

					//// Move temp file
					//stringstream temp;
					//temp << "temp." << i << ".ogg";
					//remove(temp.str().c_str());
					//rename(tempAudioFile.c_str(), temp.str().c_str());
				//}
			//}
		//}

		//// No breakout?
		//if (i == sounds.size()) {
			//qualityIncreased = true;
			//if (!(bestQuality && soundsFit == sounds.size()) || (qualityMinimized && sounds.size() == 1)) break;
			//cout << "Quality increased" << endl << endl;
		//}
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

  if (!imageUnder4MiB(file_size(imageFilePath)) && !notCorrupted(imageFilePath)) {
    return -1;
  } 

  vector<string> tags = formatAudioTags(audioFilePath.stem());
  return 0;
} 
