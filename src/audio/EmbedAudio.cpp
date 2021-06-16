#include "EmbedAudio.h"

using namespace std;
namespace fs = std::filesystem;

static bool bestQuality = true;

bool tagUnder100(unsigned int tagLength) {
  unsigned int maxTagLength = 100;
  if (tagLength < maxTagLength) {
    return true;
  }
  return false;
}

vector<string> formatAudioTags(string tag) {
  vector<string> soundTags;
  string soundTag = "[" + tag + "]";
  soundTags.push_back(soundTag); // audio.ogg ==> [audio] 
  return soundTags;
}

string createCommand(Audio::AudioData data, string cmd) {
  string command;
  string setAudioChannel = "";
  if (data.getEncodingQuality()) { setAudioChannel = " -ac 1"; } 
  //command = fmt::format(cmd,
      //data.getAudio().string(),
      //data.getAudioQuality(),
      //setAudioChannel,
      //data.getTempAudio().string(),
      //data.getTempLog().string()
      //);
  command = "NA";
  fmt::print("{}\n", command);
  return command;
}

string buildCommand(Audio::AudioData data) { return createCommand(data); }
string encodeAudio(Audio::AudioData data) {
  return createCommand(data, 
      "ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1");
}

string exec(const char* cmd, Audio::AudioData data) {
  ifstream dataContents(data.getAudio(), ifstream::in | ifstream::binary);
  vector<char> buffer(4096);

  unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) { 
    //fmt::fprintf(cerr, "Error: could not execute ffmpeg");
    clean({ data.getTempLog(), data.getTempAudio()});
    throw runtime_error("popen() failed!");
  } 

  string monoEncoding = "";
  if (data.getEncodingQuality()) { monoEncoding = "/mono"; }
  //fmt::print("Encoding \"{}\" at quality = {} {}\n\n", data.getAudio(), data.getAudioQuality(), monoEncoding);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) { ; }
  dataContents.close();

  ifstream tempFile(data.getTempAudio(), ifstream::in | ifstream::binary);
  string filedata = dataToString(tempFile);
  tempFile.close();
  return filedata;
}

void decreaseQuality(unsigned int subtrahend, Audio::AudioData& audio) {
  audio.setAudioQuality(audio.getAudioQuality() - subtrahend);
  fmt::print("Decreasing quality. Quality = {}\n", audio.getAudioQuality());
}

uintmax_t calculateTotalSize(Audio::AudioData data, fs::path imageFilePath, size_t maxFileSize = 1024 * 1024 * 4) {
  size_t tempFileSize   = sizeOf(data.getTempAudio());
  size_t imageFileSize  = sizeOf(imageFilePath);
  size_t soundTagSize   = data.getSoundTag().size();
  uintmax_t totalSize   = tempFileSize + imageFileSize + soundTagSize;

  if (!fileExists(data.getAudio()) || (tempFileSize <= 0)) {
    //fmt::fprintf(cerr, "Error: encoding failed\n");
    throw exception();
  } else 
    fmt::print("Encoding completed.\n\n");

  fmt::print("File Sizes: \n==========\n");
  fmt::print("Max File Size: {}\nTemp File Size: {}\nImage File Size: {}\nSound Tag Size: {}\n", maxFileSize, tempFileSize, imageFileSize, soundTagSize);
  fmt::print("Total size: {}\n", totalSize);

  return totalSize;
}

string encodeAudioFile(Data data) {
  Audio::AudioData& audio = data.audio;
  Image::ImageData& image = data.image;

  string cmdOutput      = exec(encodeAudio(audio).c_str(), audio);
  size_t maxFileSize    = 1024 * 1024 * 4; 
  uintmax_t totalSize   = calculateTotalSize(audio, image.getImage());
  if (totalSize > maxFileSize) {
    if (audio.getAudioQuality() == 10) {
      decreaseQuality(6, audio);
      encodeAudioFile(data);
    } else if (audio.getAudioQuality() <= 4 && audio.getAudioQuality() > 0) {
      decreaseQuality(1, audio);
      audio.setEncodingQuality(true);
      fmt::print("Setting -ac 1 option \n");
      encodeAudioFile(data);
    } else {
      fmt::print("Audio file too big, try running with -f or --fast\n");
      throw exception();
    }
  } else {
    fs::rename(audio.getTempAudio(), "temp.ogg");
    audio.getTempAudio() = "temp.ogg";
  }
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
  encodeAudioFile(data);
  encodeImage(data);
  return 0;
}
