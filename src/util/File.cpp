#include "File.h"

//namespace File {
  bool File::File::isFile(std::string file) {
    std::string ext = (std::filesystem::path (file)).extension();
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c ) { return std::tolower(c); }); 
    for (size_t i = 0; i < this->FileExtensions.size(); i++) {
      if (this->FileExtensions.at(i) == ext) { return true; }
    }
    return false;
  }
//}

bool File::File::isValid(std::string file) { return isFile(file); }
bool File::File::isValid(std::filesystem::path filepath) { return isFile(filepath.string()); }

//bool under4MiB (std::filesystem::path filepath, std::string errorMsg) {
  ////size_t fileSize = sizeOf(filepath);
  ////size_t fileSize = file_size(filepath.c_str());
  ////const char* path = filepath.c_str();
  //off_t fileSize = file_size(filepath.c_str());
  //if (fileSize > MAX_FILE_SIZE) { 
    //fmt::print(stderr, "{}\n", errorMsg);
    //return false;
  //} else
  //return true;
//} 

std::string dataToString(std::filesystem::path filepath, size_t offset) { 
  std::ifstream file(filepath, std::ifstream::in | std::ifstream::binary);
  file.seekg(offset, std::ios::beg);
  std::ostringstream fileContents;
  fileContents << file.rdbuf();
  std::string fileData = fileContents.str();
  file.close();
  return fileData;
}

//std::string readFile(std::filesystem::path filepath, size_t start, size_t end) {
  //std::ifstream file(filepath, std::ifstream::in | std::ifstream::binary); 
  //if (file.is_open()) { 
    //file.seekg(start);
    //std::string imageFile;
    //imageFile.resize(end - start);
    //file.read(&imageFile[0], end - start); 
    //return imageFile;
  //}
  //return "";
//}

bool fileExists(std::filesystem::path filepath) { 
  if(std::filesystem::exists(filepath)) { return true; } 
  fmt::print(stderr, "Error: couldn't open \"{}\"\n", filepath.string());
  return false;
}

void clean(std::initializer_list<std::filesystem::path> filepaths) {
  for(auto filepath: filepaths) { std::filesystem::remove(filepath); }
} 

//void writeToDisk(std::filesystem::path outputFileName, std::string outputData) {
  //std::ofstream outputFile(outputFileName, std::ifstream::out | std::ifstream::binary); 
  //outputFile.write(outputData.c_str(), outputData.length());
  //outputFile.close();
//} 
