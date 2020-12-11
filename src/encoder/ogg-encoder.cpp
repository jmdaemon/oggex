#include "oggex.hpp"

#include <ogg/ogg.h>

#include <stdlib.h>
#include <filesystem>

#include <iostream>
#include <fstream>

//namespace fs = std::filesystem;

//class File {
  //std::string filepath;

  //File(const std::string &filepath) {
    //this->filepath = filepath;
  //}

  
//}


//bool openFile(const fs::path& filepath, fs::file_status status = fs::file_status{}) {
  //if ( ! std::filesystem::exists(&filepath)) {
      //throw (filepath + " not found");
      //} 
  //std::fstream file;
  //file.open(filepath, ios::
//}

int main (int argc, char** argv) {
  //std::cout << "Testing bazel build file...\n"; 

  if (argc < 2) {
    // report version
    std::cout << argv[0] << " Version " << oggex_VERSION_MAJOR << "."
              << oggex_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }
}
