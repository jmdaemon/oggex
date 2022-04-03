#include "Mask.h"

using namespace std;
namespace fs = std::filesystem;
array<char, 512> hashFile(array<char, 512> buffer, size_t count) {
  unsigned long long unmaskState = 0;
  array<char, 512> maskedBuffer;
  int mask;
  for (unsigned int i = 0; i < count; ++i) {
    unmaskState = (1664525 * unmaskState + 1013904223) & 0xFFFFFFFF;
    mask = (unmaskState >> 24) & 0xFF;
    unmaskState += static_cast<unsigned int>(static_cast<unsigned char>(buffer[i] ^ mask));
    maskedBuffer[i] = buffer[i] ^ mask;
  }
  return maskedBuffer;
} 

void encodeTo(ifstream& inputFile, ofstream& outputFile, array<char, 512> buffer) {
  ostringstream contents;
  contents << inputFile.rdbuf();
  contents.seekp(0, ios::end);
  int contentSize = contents.tellp();

  outputFile << contents.rdbuf();
  hashFile(buffer, contentSize); // Write the imageFileHash to new outputFile
}
