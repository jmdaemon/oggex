#include "oggex.h"

using namespace std;
namespace fs = std::filesystem;

//string format_command() {
  //auto base   = "ffmpeg";
  //auto owout  = "-y";           // Overwrites output files without asking
  //auto noint  = "-nostdin";     // No user interaction
  //auto input  = "\"{}\"";       // Input audio file
  //auto novid  = "-vn";          // Disables video
  //auto codec_fmt = "-codec:a";  // Specifies the codec format
  //auto oggfmt = "libvorbis";    // .ogg audio format
  //auto asrfmt = "-ar ";         // Audio sampling rate
  //auto asr    = "44100" ;       // Rate of 44.1Hz for audio sampling rate/audio bitrate
  //auto wmetad = "-map_metadata";// Preserve file metadata in output. By default this will be all.
  //auto output = "\"{}\"";       // Output file name
  //auto logto  = ">> \"{}\" 2>&1";// Log all output (stdout, stderr) to this file
  
  //fmt::format("{} {} {} {}", base, owout, noint, noint, input, novid codec_fmt)

  //fmt::runtime("ffmpeg -y -nostdin -i \"{0}\" -vn -codec:a libvorbis -ar 44100 -aq {1}{2} -map_metadata -1 \"{3}\" >> \"{4}\" 2>&1")
//}

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

size_t getOffset(std::filesystem::path filepath, const char* searchTerm) { 
  off_t offset = dataToString(filepath, 0, file_size(filepath.c_str())).find(searchTerm);
  if (file_size(filepath.c_str()) == offset) {
    fmt::print(stderr, "Audio offset not found");
    offset = 0;
  }
  return offset; 
}

string findSoundTag(Data& data, string fileData, size_t offset) {
  string tag = fileData.substr(0, offset);
  size_t endTag = tag.rfind("]"); 
  size_t startTag = tag.rfind("[");
  if (endTag == std::string::npos || startTag == std::string::npos) {
    fmt::print("Sound Tag not found.\n");
    return "";
  }
  string unstrippedTag = tag.substr(startTag, endTag); // soundTag = [audio02] => audio02
  string soundTag = (!isEmpty(unstrippedTag, "Sound Tag was not found.")) 
    ?  unstrippedTag.substr(1,  unstrippedTag.length() - 2) : ""; 

  if (data.options.showVerboseEnabled()) { 
    fmt::print("\n================ Sound Tag ================\n");
    printSize("Tag", unstrippedTag);
    printSize("Stripped Tag", soundTag);
  }
  return soundTag; 
} 

int extract(Data data) {
  std::filesystem::path image = data.image.getImage();
  size_t embeddedFileSize   = file_size(image.c_str());
  size_t audioOffset        = getOffset(image);
  size_t audioFileSize      = file_size(image.c_str()) +  audioOffset;

  if (data.options.showVerboseEnabled()) { printExtractSizes(data, embeddedFileSize, audioFileSize, audioOffset); }

  string embeddedFileData   = dataToString(image, 0, file_size(image.c_str()));
  string imageFileData      = read_slice(image.c_str(), 0, audioOffset);
  string audioContent       = dataToString(image, audioOffset, file_size(image.c_str()));
  string soundTag           = findSoundTag(data, embeddedFileData, audioOffset); 
  if (soundTag.empty()) {
    return -1; 
  } else 
      soundTag += ".ogg";
  if (data.options.showVerboseEnabled()) { printSize("Output Audio File", soundTag); }
  fmt::print("Extracting audio file as \"{}\"\n", soundTag);

  fs::path audioFileName = (data.options.audioFileEnabled()) ?  fs::path(data.options.getAudioFile()) : soundTag.c_str(); 
  fs::path imageFileName = (data.options.imageFileEnabled()) ?  fs::path(data.options.getImageFile()) : fs::path(image.string() + ".png");
  write_file(audioFileName.c_str(), audioContent.c_str());
  write_file(imageFileName.c_str(), imageFileData.c_str());

  return 0;
}
