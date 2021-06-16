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

bool fileExists(std::filesystem::path filepath);
void cleanTempFiles(std::filesystem::path tempLogFile, std::filesystem::path tempAudioFile);

bool tagUnder100(unsigned int tagLength);
std::vector<std::string> formatAudioTags(std::string tag);

std::string createCommand(Audio::AudioData data, 
    std::string cmd = "ffmpeg -y -nostdin -i \"{}\" -vn acodec libvorbis -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1");
std::string buildCommand(Audio::AudioData data);
std::string encodeAudio(Audio::AudioData data);

std::string exec(const char* cmd, Audio::AudioData data);

void encodeImage(std::filesystem::path imageFilePath, std::string soundTag, std::filesystem::path encodedAudioFilePath = "out.ogg");
//int embed(std::filesystem::path audioFilePath, std::filesystem::path imageFilePath, std::string soundTag, bool quality);
int embed(Data data);

#endif
