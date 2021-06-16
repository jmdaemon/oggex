#include "ExtractAudio.h"

using namespace std;
namespace fs = std::filesystem;

size_t getAudioOffset(ifstream& file, const char* search_term) {
  size_t file_size = sizeOf(file);
  fmt::print("Size of Embedded File \t\t: {} \tbytes\n", file_size);
  size_t audioOffset = dataToString(file).find(search_term);

  if (file_size == audioOffset) {
    fmt::print(stderr, "Audio offset not found");
    audioOffset = 0;
  }
  return audioOffset; 
}

string readFile(fs::path filepath, size_t offset) {
  ifstream file(filepath, ifstream::in | ifstream::binary);
  fmt::print("Audio File Size \t\t: {} \tbytes\n", sizeOf(file)); 
  file.seekg(offset, ios::beg);

  string result = dataToString(file);
  file.close();

  return result;
}

string findSoundTag(fs::path filepath, size_t offset) {
  ifstream file(filepath, ifstream::in | ifstream::binary);
  string fileData = dataToString(file);
  file.close();

  string tag = fileData.substr(offset - 100, offset);
  //fmt::print("Tag: \t\t\t\t: {}\n", tag);
  //regex exp("(\\[\\w+\\])(\?!OggS)");
  regex exp("(\\[\\w+\\])");
  //regex exp("(\\w+)");

  string soundTag = "";
  smatch match;
  if (regex_search(tag, match, exp)) { 
    fmt::print("Found Sound Tag: \t\t: {}\n", soundTag);
    soundTag = match[0]; // tag = [audio02].ogg
  }
  string result = soundTag.substr(1,  soundTag.length() - 2); // tag = audio02.ogg
  fmt::print("Stripped Sound Tag: \t\t: {}\n", result);
  return result; 
}

int extract(Data data) {
  Image::ImageData& image = data.image;

  // Find section where ogg file begins.
  // Find audio tag, store in string
  // Slice image file into two
  // - Read the audio file path after the image file start, until file end
  // Write to new audio file with audio tag
  ifstream file(image.getImage(), ifstream::in | ifstream::binary);

  size_t audioOffset = getAudioOffset(file);
  fmt::print("Audio File Offset \t\t: {} \tbytes\n", audioOffset); 
  file.close();

  string audioContent = readFile(image.getImage(), audioOffset);
  string soundTag     = findSoundTag(image.getImage(), audioOffset) + ".ogg"; 
  fmt::print("Sound tag \t\t\t: \"{}\"\n\n", soundTag);

  ofstream audioFile(soundTag.c_str(), ifstream::out | ifstream::binary); 
  audioFile.write(audioContent.c_str(), audioContent.length());

  audioFile.close();

   return 0;
}
