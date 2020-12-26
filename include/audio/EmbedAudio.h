#ifndef EMBEDAUDIO_H
#define EMBEDAUDIO_H

#include <string>
#include <filesystem>
#include <cstdint>
#include <vector>

#include "FileType.tpp"
#include "Audio.h"

void cleanTempFiles(std::filesystem::path tempLogFile, std::filesystem::path tempAudioFile);

bool tagUnder100(unsigned int tagLength);
std::vector<std::string> formatAudioTags(std::string tag);

std::string createCommand(Audio::AudioData data, 
    std::string cmd = "ffmpeg -y -nostdin -i \"{}\" -vn acodec libvorbis -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1");
std::string buildCommand(Audio::AudioData data);
std::string encodeAudio(Audio::AudioData data);

std::string exec(const char* cmd, Audio::AudioData data);

void encodeImage(std::filesystem::path imageFilePath, std::string encodedAudio, std::string soundTag, std::filesystem::path encodedAudioFilePath = "out.ogg");


int embed(std::filesystem::path audioFilePath, std::filesystem::path imageFilePath, std::string soundTag, bool quality);

#endif
