#include "File.h"

namespace File {
  std::string toLowerCase(const std::filesystem::path& filePath) {
    std::string fpath = filePath.string();
    std::transform(fpath.begin(), fpath.end(), fpath.begin(), 
        [](unsigned char c ) { return std::tolower(c); }); 
    return fpath;
  }

  std::string getFileExtension(std::string file) {
    return (std::filesystem::path (file)).extension();
  }

  bool File::isFile(std::string file, const std::map<int, std::string> FileExtensions) {
    std::string extension = toLowerCase(getFileExtension(file));
    for (int i = 0; i < FileExtensions.size(); i++) {
      if(FileExtensions.at(i) == extension) {
        return true;
      }
    }
    return false;
  }
}

size_t sizeOf(std::ifstream& file, size_t offset) {
  file.seekg(0, std::ios::end);
  size_t fileSize = file.tellg();
  file.seekg(0, std::ios::beg);
  file.close();
  return fileSize - offset;
}

size_t sizeOf(std::filesystem::path filepath, size_t offset) {
  std::ifstream file(filepath, std::ifstream::in | std::ifstream::binary);
  return sizeOf(file); 
}

bool under4MiB (std::filesystem::path filepath, std::string errorMsg) {
  size_t fileSize = sizeOf(filepath);
  if (fileSize > MAX_FILE_SIZE) { 
    fmt::print(stderr, "{}\n", errorMsg);
    return false;
  } else
  return true;
} 

std::string dataToString(std::filesystem::path filepath, size_t offset) { 
  std::ifstream file(filepath, std::ifstream::in | std::ifstream::binary);
  file.seekg(offset, std::ios::beg);
  std::ostringstream fileContents;
  fileContents << file.rdbuf();
  std::string fileData = fileContents.str();
  file.close();
  return fileData;
}

std::string readFile(std::filesystem::path filepath, size_t start, size_t end) {
  std::ifstream file(filepath, std::ifstream::in | std::ifstream::binary); 
  if(file.is_open()) { 
    file.seekg(start);
    std::string imageFile;
    imageFile.resize(end - start);
    file.read(&imageFile[0], end - start); 
    return imageFile;
  }
  return "";
}

bool fileExists(std::filesystem::path filepath) { 
  std::ifstream file(filepath, std::ifstream::in | std::ifstream::binary);
  if (!file.is_open()) {
    fmt::print(stderr, "Error: couldn't open \"{}\"\n", filepath.string());
    file.close();
    return false; 
  } 
  file.close();
  return true; 
}

void clean(std::initializer_list<std::filesystem::path> filepaths) {
  for( auto filepath: filepaths) {
    std::filesystem::remove(filepath);
  }
} 

void writeToDisk(std::filesystem::path outputFileName, std::string outputData) {
  std::ofstream outputFile(outputFileName, std::ifstream::out | std::ifstream::binary); 
  outputFile.write(outputData.c_str(), outputData.length());
  outputFile.close();
} 
