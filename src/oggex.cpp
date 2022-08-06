#include "oggex.h"

std::string dataToString(std::filesystem::path filepath, off_t beg, off_t end) { 
  const std::string slice = read_slice(filepath.c_str(), beg, end);
  return slice;
}

using namespace std;
namespace fs = std::filesystem;

//string format_command() {
  //auto base   = "ffmpeg";
  //auto owout  = "-y";           // Overwrites output files without asking
  //auto noint  = "-nostdin";     // No user interaction
  //auto input  = "\"{}\"";       // Input audio file
  //auto novid  = "-vn";          // Disables video
  //auto codec_fmt = "-codec:a {}";// Specifies the codec format
  //auto oggfmt = "libvorbis";    // .ogg audio format
  //auto asrfmt = "-ar {}";       // Audio sampling rate
  //auto asr    = "44100" ;       // Rate of 44.1Hz for audio sampling rate/audio bitrate
  //auto wmetad = "-map_metadata";// Preserve file metadata in output. By default this will be all.
  //auto output = "\"{}\"";       // Output file name
  //auto logto  = ">> \"{}\" 2>&1";// Log all output (stdout, stderr) to this file
  
  //fmt::format(fmt::runtime
      //("ffmpeg {} {} {} {} {} {5} {}",
       //owout, noint, noint, input, novid, codec_fmt, oggfmt))

  //fmt::runtime("ffmpeg -y -nostdin -i \"{0}\" -vn -codec:a libvorbis -ar 44100 -aq {1}{2} -map_metadata -1 \"{3}\" >> \"{4}\" 2>&1")
//}

string createCommand(Media& media) {
  //Audio::AudioData& audio = data.audio;
  auto sound = media.sound;
  auto settings = media.settings;
  string enableMono = (media.options.isMonoEnabled()) ? " -ac 1" : "";
  string command = fmt::format(fmt::runtime("ffmpeg -y -nostdin -i \"{0}\" -vn -codec:a libvorbis -ar 44100 -aq {1}{2} -map_metadata -1 \"{3}\" >> \"{4}\" 2>&1"),
      string(sound.src), settings.quality, enableMono, sound.temp, sound.log);
  if (media.options.showVerboseEnabled()) {
    fmt::print("{}\n", command);
  }
  return command;
}

//string encode(const string cmd, Data& data) {
string encode(const string cmd, Media& media) {
  //Audio::AudioData& audio = data.audio;
  auto sound = media.sound;
  auto settings = media.settings;
  string monoAudioEnabled = (media.options.isMonoEnabled()) ? "In Mono Audio Channel" : "";
  fmt::print("Encoding \"{}\" at quality = {} {}\n", string(sound.src), settings.quality, monoAudioEnabled);
  /* Execute command */
  exec(cmd.c_str(), 4096);
  /* Return temp audio file */
  string result = dataToString(sound.temp, 0, file_size(sound.temp));
  return result;
}

// This should be a function named size() thats available on the 
// data structure that holds all the files
//uintmax_t calcFinalSize(Data& data, size_t maxFileSize) {
uintmax_t calcFinalSize(Media& media, size_t maxFileSize) {
  auto sound = media.sound;
  size_t tempFileSize   = file_size(sound.src);
  size_t imageFileSize  = file_size(sound.dest);
  size_t soundTagSize   = sizeof(sound.tag);
  uintmax_t finalSize   = tempFileSize + imageFileSize + soundTagSize;

  if (tempFileSize <= 0) {
    fmt::print(stderr, "Error: encoding failed\n");
    throw exception();
  } 

  //if (media.options.showVerboseEnabled()) { printEmbedSizes(data, maxFileSize, tempFileSize, imageFileSize, soundTagSize, finalSize); }
  return finalSize;
}

// this is weird and doesn't directly do what the function name suggests
void removeTemp(Media& media) {
  fmt::print("Audio Encoding completed.\n\n");
  fs::rename(media.sound.temp, "temp.ogg");
}

string encodeAudio(Media& media, bool decreaseQuality) {
  auto settings = media.settings;
  auto options = media.options;
  string cmdOutput; 

  while (true) {
    cmdOutput = encode(createCommand(media), media);
    // Do the encoding
    uintmax_t finalSize = calcFinalSize(media, MAX_FILE_POST_SIZE);
    // If we don't care about the limit
    if (options.ignoreLimitEnabled()) {
      // Then do the encoding once
      // Note that in the future, this would be better as a direct copy rather than re-encoding.
      break;
    }

    // Else re-encode
    if (finalSize < MAX_FILE_POST_SIZE) {
      break;
    } else if (decreaseQuality) {
      if (settings.quality > 0)
        settings.quality -= 6; // Decrease sound quality if file size exceeds our limit
    } else {
      fmt::print("Audio file is too big (>4MiB), try running with -f or --fast\n");
      throw exception();
    }
  }

  fmt::print("Audio Encoding completed.\n\n");
  return cmdOutput;
}

//void encodeImage(Data& data) {
void encodeImage(Media& media) {
  //Audio::AudioData& audio = data.audio;
  auto sound = media.sound;
  auto settings = media.settings;

  if (!file_exists(sound.src)) { 
    fmt::print(stderr, "Image or Audio file does not exist or is being blocked\n");
    //clean({audio.getTempAudio()});
    remove(sound.temp);
    throw exception();
  } 

  fs::path outputFileName = (media.options.outputFileEnabled()) ?  fs::path(media.options.getOutputFile()) : fs::path(sound.dest); 
  ofstream outputFile(outputFileName, ifstream::out | ifstream::binary);
  ifstream imageFileData(sound.dest, ifstream::in | ifstream::binary);
  ifstream audioFileData(sound.temp, ifstream::in | ifstream::binary);

  outputFile << imageFileData.rdbuf() << formatSoundTag(sound.tag) << audioFileData.rdbuf();
  outputFile.close();
  imageFileData.close();
  audioFileData.close();
  remove(sound.temp);
}

//int embed(Data& data) {
int embed(Media& media) {
  encodeAudio(media);
  encodeImage(media);
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

//string findSoundTag(Data& data, string fileData, size_t offset) {
string findSoundTag(Media& media, string fileData, size_t offset) {
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

  if (media.options.showVerboseEnabled()) { 
    fmt::print("\n================ Sound Tag ================\n");
    printSize("Tag", unstrippedTag);
    printSize("Stripped Tag", soundTag);
  }
  return soundTag; 
} 

int extract(Media& media) {
  //std::filesystem::path image = data.image;
  auto sound = media.sound;
  auto settings = media.settings;
  auto image = sound.dest;

  size_t embeddedFileSize   = file_size(image);
  size_t audioOffset        = getOffset(image);
  size_t audioFileSize      = file_size(image) +  audioOffset;

  //if (settings.options.showVerboseEnabled()) { printExtractSizes(data, embeddedFileSize, audioFileSize, audioOffset); }

  string embeddedFileData   = dataToString(image, 0, file_size(image));
  string imageFileData      = read_slice(image, 0, audioOffset);
  string audioContent       = dataToString(image, audioOffset, file_size(image));
  string soundTag           = findSoundTag(media, embeddedFileData, audioOffset); 
  if (soundTag.empty()) {
    return -1; 
  } else 
      soundTag += ".ogg";
  if (media.options.showVerboseEnabled()) { printSize("Output Audio File", soundTag); }
  fmt::print("Extracting audio file as \"{}\"\n", soundTag);

  //fs::path audioFileName = (media.options.audioFileEnabled()) ?  fs::path(data.options.getAudioFile()) : soundTag.c_str(); 
  //fs::path imageFileName = (media.options.imageFileEnabled()) ?  fs::path(data.options.getImageFile()) : fs::path(image.string() + ".png");
  auto audioFileName = (media.options.audioFileEnabled()) ?  sound.src : soundTag.c_str(); 
  auto imageFileName = (media.options.imageFileEnabled()) ?  sound.dest : string(sound.dest) + ".png";

  write_file(audioFileName, audioContent.c_str());
  write_file(imageFileName.c_str(), imageFileData.c_str());

  return 0;
}
