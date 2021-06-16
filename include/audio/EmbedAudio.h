#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Image.h"
#include "Audio.h"
#include "Data.h"
#include "Mask.h"

#include "FileType.tpp"


const size_t MAX_FILE_SIZE = 1024 * 1024 * 4; 

bool fileExists(std::filesystem::path filepath);
void cleanTempFiles(std::filesystem::path tempLogFile, std::filesystem::path tempAudioFile);

std::string createCommand(Audio::AudioData data);
std::string exec(const std::string, Audio::AudioData data);

std::string encodeAudio(Data data, bool decreaseQuality = false);
void encodeImage(Data data);
int embed(Data data);

#endif
