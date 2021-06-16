#include "EmbedAudio.h"

using namespace std;
namespace fs = std::filesystem;

string createCommand(Audio::AudioData data) {
  string command;
  if (data.getEncodingQuality()) { 
    command = fmt::format(
        "ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {} -ac 1 -map_metadata -1 \"{}\" >> \"{}\" 2>&1",
      data.getAudio().string(), data.getAudioQuality(), data.getTempAudio().string(), data.getTempLog().string()
        );
  } else {
    command = fmt::format(
        "ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1",
      data.getAudio().string(), data.getAudioQuality(), data.getTempAudio().string(), data.getTempLog().string()
        );
    }
  fmt::print("{}\n", command);
  return command;
}

string exec(const string cmd, Audio::AudioData audio) {
  ifstream audioFileData(audio.getAudio(), ifstream::in | ifstream::binary);
  vector<char> buffer(4096);

  unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
  if (!pipe) { 
    fmt::print(stderr, "Error: could not execute ffmpeg");
    clean({ audio.getTempLog(), audio.getTempAudio()});
    throw runtime_error("popen() failed!");
  } 

  string monoEncoding = "";
  if (audio.getEncodingQuality()) { monoEncoding = "/mono"; }
  fmt::print("Encoding \"{}\" at quality = {} {}\n\n", audio.getAudio().string(), audio.getAudioQuality(), monoEncoding);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) { ; }
  audioFileData.close();

  ifstream tempFile(audio.getTempAudio(), ifstream::in | ifstream::binary);
  string filedata = dataToString(tempFile);
  tempFile.close();
  return filedata;
}

uintmax_t calculateTotalSize(Data data, size_t maxFileSize) {
  Audio::AudioData& audio = data.audio;
  Image::ImageData& image = data.image;

  size_t tempFileSize   = sizeOf(audio.getTempAudio());
  size_t imageFileSize  = sizeOf(image.getImage());
  size_t soundTagSize   = audio.getSoundTag().size();
  uintmax_t totalSize   = tempFileSize + imageFileSize + soundTagSize;

  if (tempFileSize <= 0) {
    fmt::print(stderr, "Error: encoding failed\n");
    throw exception();
  } else 
    fmt::print("Encoding completed.\n\n");

  fmt::print("File Sizes: \n==========\n");
  fmt::print("Max File Size: {}\nTemp File Size: {}\nImage File Size: {}\nSound Tag Size: {}\n", maxFileSize, tempFileSize, imageFileSize, soundTagSize);
  fmt::print("Total size: {}\n", totalSize);
  return totalSize;
}

string encodeAudio(Data data, bool decreaseQuality) {
  Audio::AudioData& audio = data.audio;
  Image::ImageData& image = data.image;

  string cmdOutput      = exec(createCommand(audio), audio);
  uintmax_t finalSize   = calculateTotalSize(data, MAX_FILE_SIZE);

  if (!data.ignoreSizeLimit) {
    if (finalSize < MAX_FILE_SIZE) { 
      encodeAudio(data);
    } else if (decreaseQuality && audio.getAudioQuality() > 0) { 
      audio.decreaseQuality(6); // Decrease sound quality if file size exceeds our limit
      encodeAudio(data);
    } else {
        fmt::print("Audio file is too big (>4MiB), try running with -f or --fast\n");
        throw exception();
      }
  } else { // Ignore file size limits
    encodeAudio(data);
  }
  fs::rename(audio.getTempAudio(), "temp.ogg");
  audio.getTempAudio() = "temp.ogg";
  return cmdOutput;
}

void encodeImage(Data data) {
  Audio::AudioData& audio = data.audio;
  Image::ImageData& image = data.image;

  if (!fileExists(audio.getTempAudio())) { 
    fmt::print(stderr, "Image or Audio file does not exist or is being blocked\n");
    clean({image.getImage(), audio.getTempAudio()});
    throw exception();
  }

  ofstream outputFile(image.createOutputFilename(), ifstream::out | ifstream::binary);
  ifstream imageFileData(image.getImage(), ifstream::in | ifstream::binary);
  ifstream audioFileData(audio.getTempAudio(), ifstream::in | ifstream::binary);

  outputFile << imageFileData.rdbuf() << audio.getSoundTag() << audioFileData.rdbuf();
  outputFile.close();
  imageFileData.close();
  audioFileData.close();
  clean({audio.getTempAudio()});
}

int embed(Data data) {
  encodeAudio(data);
  encodeImage(data);
  return 0;
}
