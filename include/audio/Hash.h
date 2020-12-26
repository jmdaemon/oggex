#ifndef HASH_H
#define HASH_H

#include <array>
#include <fstream>

std::array<char, 512> hashFile(std::array<char, 512> buffer, size_t count);
void encodeTo(std::ifstream& inputFile, std::ofstream& outputFile, std::array<char, 512> buffer);


#endif
