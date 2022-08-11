#include "oggex.h"

std::string dataToString(std::filesystem::path filepath, off_t beg, off_t end) { 
  const std::string slice = read_slice(filepath.c_str(), beg, end);
  return slice;
}

/**
  * FFmpeg command used:
  * ffmpeg -y         \ # Overwrites output files without asking
  * -nostdin          \ # No user interaction
  * -i \"{}\"         \ # Input audio file
  * -vn               \ # Disables video
  * -codec:a {}       \ # Specifies the codec format
  * libvorbis         \ # .ogg audio format
  * -ar 44100         \ # Set audio sampling rate (44.1Hz).
  * -map_metadata -1  \ # Preserve file metadata in output. By default this will be all.
  * \"{}\"            \ # Output to file
  * >> \"{}\" 2>&1    \ # Log all output (stdout, stderr) to this file
  */
std::string format_command(Media& media) {
  auto sound = media.sound;
  auto settings = media.settings;
  auto mono_option = (media.options.isMonoEnabled()) ? " -ac 1" : "";
  auto command = fmt::format(fmt::runtime(
        "ffmpeg -y -nostdin -i \"{0}\" -vn -codec:a libvorbis -ar 44100 -aq {1}{2} -map_metadata -1 \"{3}\" >> \"{4}\" 2>&1"
        ), sound.src, settings.quality, mono_option, sound.temp, sound.log);
  spdlog::debug("{}\n", command);
  return command;
}

void encode(const std::string cmd, Media& media) {
  auto sound = media.sound;
  auto settings = media.settings;
  auto use_mono_encoding = (media.options.isMonoEnabled()) ? "In Mono Audio Channel" : "";
  spdlog::info("Encoding \"{}\" at quality = {} {}\n", sound.src, settings.quality, use_mono_encoding);
  exec(cmd.c_str(), 4096);
}

uintmax_t embed_size(Sound& sound) {
  size_t temp   = file_size(sound.src);
  size_t image  = file_size(sound.dest);
  size_t tag    = sizeof(sound.tag);
  uintmax_t embed_size = temp + image + tag;

  if (temp <= 0) {
    spdlog::error("Error: encoding failed");
    throw std::exception();
  } 

  return embed_size;
}

void encodeAudio(Media& media) {
  auto settings = media.settings;
  auto options = media.options;
  std::string cmdOutput; 

  while (true) {
    encode(format_command(media), media); // Note that doing an initial direct copy in embed would be better
    uintmax_t finalSize = embed_size(media.sound);
    // If we don't care about the limit
    if (options.ignoreLimitEnabled())
      break;

    // Else re-encode
    if (finalSize < MAX_FILE_POST_SIZE) {
      break;
    } else if (settings.quality > 0) {
        settings.quality -= 6; // Decrease sound quality if file size exceeds our limit
    } else {
      spdlog::error("Audio file is too big (>4MiB), try running with -f or --fast\n");
      throw std::exception();
    }
  }
  spdlog::info("Audio Encoding completed.\n\n");
}

void encodeImage(Media& media) {
  auto sound = media.sound;
  auto settings = media.settings;

  if (!file_exists(sound.src)) { 
    spdlog::error("Image or Audio file does not exist or is being blocked");
    remove(sound.temp);
    throw std::exception();
  } 

  auto outputFileName = (media.options.outputFileEnabled()) ? 
    std::filesystem::path(media.options.getOutputFile()) : std::filesystem::path(sound.dest); 
  std::ofstream outputFile(outputFileName, std::ifstream::out | std::ifstream::binary);
  std::ifstream imageFileData(sound.dest, std::ifstream::in | std::ifstream::binary);
  std::ifstream audioFileData(sound.temp, std::ifstream::in | std::ifstream::binary);

  outputFile << imageFileData.rdbuf() << "[" << sound.tag << "]" << audioFileData.rdbuf();
  outputFile.close();
  imageFileData.close();
  audioFileData.close();
  remove(sound.temp);
}

int embed(Media& media) {
  encodeAudio(media);
  encodeImage(media);
  return 0;
}

size_t getOffset(std::filesystem::path filepath, const char* searchTerm) { 
  off_t offset = dataToString(filepath, 0, file_size(filepath.c_str())).find(searchTerm);
  if (file_size(filepath.c_str()) == offset) {
    spdlog::warn("Audio offset not found");
    offset = 0;
  }
  return offset; 
}

std::string findSoundTag(Media& media, std::string fileData, size_t offset) {
  auto tag = fileData.substr(0, offset);
  size_t endTag = tag.rfind("]"); 
  size_t startTag = tag.rfind("[");
  if (endTag == std::string::npos || startTag == std::string::npos) {
    spdlog::warn("Sound Tag not found.\n");
    return "";
  }
  std::string unstrippedTag = tag.substr(startTag, endTag); // soundTag = [audio02] => audio02

  std::string soundTag = "";
  if (!unstrippedTag.empty()) {
    spdlog::warn("Sound Tag was not found.");
    soundTag = unstrippedTag.substr(1,  unstrippedTag.length() - 2);
  }

  // TODO: Display sound tag
  //if (media.options.showVerboseEnabled()) { 
    //fmt::print("\n================ Sound Tag ================\n");
    //printSize("Tag", unstrippedTag);
    //printSize("Stripped Tag", soundTag);
  //}
  return soundTag; 
}

int extract(Media& media) {
  auto sound = media.sound;
  auto image = sound.dest;

  size_t embeddedFileSize   = file_size(image);
  size_t audioOffset        = getOffset(image);
  size_t audioFileSize      = file_size(image) +  audioOffset;

  //if (settings.options.showVerboseEnabled()) { printExtractSizes(data, embeddedFileSize, audioFileSize, audioOffset); }

  std::string embeddedFileData   = dataToString(image, 0, file_size(image));
  std::string imageFileData      = read_slice(image, 0, audioOffset);
  std::string audioContent       = dataToString(image, audioOffset, file_size(image));
  std::string soundTag           = findSoundTag(media, embeddedFileData, audioOffset); 
  if (soundTag.empty()) {
    return -1; 
  } else 
      soundTag += ".ogg";

  // TODO: Show size of output files
  //if (media.options.showVerboseEnabled()) { printSize("Output Audio File", soundTag); }
  spdlog::info("Extracting audio file as \"{}\"\n", soundTag);

  //fs::path audioFileName = (media.options.audioFileEnabled()) ?  fs::path(data.options.getAudioFile()) : soundTag.c_str(); 
  //fs::path imageFileName = (media.options.imageFileEnabled()) ?  fs::path(data.options.getImageFile()) : fs::path(image.string() + ".png");
  auto audioFileName = (media.options.audioFileEnabled()) ?  sound.src : soundTag.c_str(); 
  auto imageFileName = (media.options.imageFileEnabled()) ?  sound.dest : std::string(sound.dest) + ".png";

  write_file(audioFileName, audioContent.c_str());
  write_file(imageFileName.c_str(), imageFileData.c_str());

  return 0;
}

std::array<char, 512> hashFile(std::array<char, 512> buffer, size_t count) {
  unsigned long long unmaskState = 0;
  std::array<char, 512> maskedBuffer;
  int mask;
  for (unsigned int i = 0; i < count; ++i) {
    unmaskState = (1664525 * unmaskState + 1013904223) & 0xFFFFFFFF;
    mask = (unmaskState >> 24) & 0xFF;
    unmaskState += static_cast<unsigned int>(static_cast<unsigned char>(buffer[i] ^ mask));
    maskedBuffer[i] = buffer[i] ^ mask;
  }
  return maskedBuffer;
} 

void encodeTo(std::ifstream& inputFile, std::ofstream& outputFile, std::array<char, 512> buffer) {
  std::ostringstream contents;
  contents << inputFile.rdbuf();
  contents.seekp(0, std::ios::end);
  int contentSize = contents.tellp();

  outputFile << contents.rdbuf();
  hashFile(buffer, contentSize); // Write the imageFileHash to new outputFile
}
