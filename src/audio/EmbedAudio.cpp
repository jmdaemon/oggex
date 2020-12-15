#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <filesystem> // C++17

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


