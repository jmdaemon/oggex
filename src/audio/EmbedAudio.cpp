#include "EmbedAudio.h"

using namespace std;
namespace fs = std::filesystem;

string createCommand(Data& data) {
  Audio::AudioData& audio = data.audio;
  string enableMono = (data.options.isMonoEnabled()) ? " -ac 1" : "";
  string command = fmt::format(fmt::runtime("ffmpeg -y -nostdin -i \"{0}\" -vn -codec:a libvorbis -ar 44100 -aq {1}{2} -map_metadata -1 \"{3}\" >> \"{4}\" 2>&1"),
      audio.getAudio().string(), audio.getAudioQuality(), enableMono, audio.getTempAudio().string(), audio.getTempLog().string());
  if (data.options.showVerboseEnabled()) {
    fmt::print("{}\n", command);
  }
  return command;
}

string encode(const string cmd, Data& data) {
  Audio::AudioData& audio = data.audio;
  string monoAudioEnabled = (data.options.isMonoEnabled()) ? "In Mono Audio Channel" : "";
  fmt::print("Encoding \"{}\" at quality = {} {}\n", audio.getAudio().string(), audio.getAudioQuality(), monoAudioEnabled);
  /* Execute command */
  exec(cmd.c_str(), 4096);
  /* Return temp audio file */
  string result = dataToString(audio.getTempAudio(), 0, file_size(audio.getTempAudio()));
  return result;
}

uintmax_t calcFinalSize(Data& data, size_t maxFileSize) {
  size_t tempFileSize   = file_size(data.audio.getTempAudio().c_str());
  size_t imageFileSize  = file_size(data.image.getImage().c_str());
  size_t soundTagSize   = data.audio.getSoundTag().size();
  uintmax_t finalSize   = tempFileSize + imageFileSize + soundTagSize;

  if (tempFileSize <= 0) {
    fmt::print(stderr, "Error: encoding failed\n");
    throw exception();
  } 

  if (data.options.showVerboseEnabled()) { printEmbedSizes(data, maxFileSize, tempFileSize, imageFileSize, soundTagSize, finalSize); }
  return finalSize;
}

void removeTemp(Data& data) {
  fmt::print("Audio Encoding completed.\n\n");
  fs::rename(data.audio.getTempAudio(), "temp.ogg");
  data.audio.setTempAudio(fs::path("temp.ogg"));
}

string encodeAudio(Data& data, bool decreaseQuality) {
  Audio::AudioData& audio = data.audio;
  string cmdOutput      = encode(createCommand(data), data);
  uintmax_t finalSize   = calcFinalSize(data, MAX_FILE_SIZE);

  if (!data.options.ignoreLimitEnabled()) {
    if (finalSize < MAX_FILE_SIZE) { 
      removeTemp(data);
      return cmdOutput;
    } else if (decreaseQuality) { 
      if (audio.getAudioQuality() > 0) {
        audio.decreaseQuality(6); // Decrease sound quality if file size exceeds our limit
        encodeAudio(data);
      }
    } else {
        fmt::print("Audio file is too big (>4MiB), try running with -f or --fast\n");
        throw exception();
      }
  } // Ignore file size limits
  removeTemp(data);
  return cmdOutput;
}

void encodeImage(Data& data) {
  Audio::AudioData& audio = data.audio;

  if (!file_exists(audio.getTempAudio().c_str())) { 
    fmt::print(stderr, "Image or Audio file does not exist or is being blocked\n");
    clean({audio.getTempAudio()});
    throw exception();
  } 

  fs::path outputFileName = (data.options.outputFileEnabled()) ?  fs::path(data.options.getOutputFile()) : data.image.createOutputFilename(); 
  ofstream outputFile(outputFileName, ifstream::out | ifstream::binary);
  ifstream imageFileData(data.image.getImage(), ifstream::in | ifstream::binary);
  ifstream audioFileData(audio.getTempAudio(), ifstream::in | ifstream::binary);

  outputFile << imageFileData.rdbuf() << formatSoundTag(audio.getSoundTag()) << audioFileData.rdbuf();
  outputFile.close();
  imageFileData.close();
  audioFileData.close();
  clean({audio.getTempAudio()});
}

int embed(Data& data) {
  encodeAudio(data);
  encodeImage(data);
  return 0;
}
