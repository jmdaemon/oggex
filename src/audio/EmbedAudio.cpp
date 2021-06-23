#include "EmbedAudio.h"
#include <iosfwd>

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

string exec(const string cmd, Data& data) {
  Audio::AudioData& audio = data.audio;
  ifstream audioFileData(audio.getAudio(), ifstream::in | ifstream::binary);
  vector<char> buffer(4096);

  unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
  if (!pipe) { 
    fmt::print(stderr, "Error: could not execute ffmpeg");
    clean({ audio.getTempLog(), audio.getTempAudio()});
    throw runtime_error("popen() failed!");
  } 

  string monoAudioEnabled = (data.options.showVerboseEnabled()) ? "In Mono Audio Channel" : "";
  fmt::print("Encoding \"{}\" at quality = {} {}\n", audio.getAudio().string(), audio.getAudioQuality(), monoAudioEnabled);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) { ; }
  audioFileData.close();
  return dataToString(audio.getTempAudio());
}

uintmax_t calcFinalSize(Data& data, size_t maxFileSize) {
  size_t tempFileSize   = sizeOf(data.audio.getTempAudio());
  size_t imageFileSize  = sizeOf(data.image.getImage());
  size_t soundTagSize   = data.audio.getSoundTag().size();
  uintmax_t finalSize   = tempFileSize + imageFileSize + soundTagSize;

  if (tempFileSize <= 0) {
    fmt::print(stderr, "Error: encoding failed\n");
    throw exception();
  } 

  if (data.options.showVerboseEnabled()) { 
    std::map<int, std::tuple<std::string, size_t>> sizes = {
      { 0, std::make_tuple("Max File Size"  , maxFileSize)},
      { 1, std::make_tuple("Temp File Size" , tempFileSize)},
      { 2, std::make_tuple("Image File Size", imageFileSize)},
      { 3, std::make_tuple("Sound Tag Size" , soundTagSize)},
      { 4, std::make_tuple("Final Size"     , finalSize)}
    };

    fmt::print("\n================ File Sizes ================\n");
    for (auto const& [key, sizeTuple] : sizes)
      printSize(data, sizeTuple, 16); 
  }
  return finalSize;
}

void removeTemp(Data& data) {
  fmt::print("Audio Encoding completed.\n\n");
  fs::rename(data.audio.getTempAudio(), "temp.ogg");
  data.audio.setTempAudio(fs::path("temp.ogg"));
}

string encodeAudio(Data& data, bool decreaseQuality) {
  Audio::AudioData& audio = data.audio;
  string cmdOutput      = exec(createCommand(data), data);
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

  if (!fileExists(audio.getTempAudio())) { 
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
