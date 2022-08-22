#include "oggex.h"

// Embed

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
  auto mono_option = (media.args.mono_encoding) ? " -ac 1" : "";
  auto command = fmt::format(fmt::runtime(
        "ffmpeg -y -nostdin -i \"{0}\" -vn -codec:a libvorbis -ar 44100 -aq {1}{2} -map_metadata -1 \"{3}\" >> \"{4}\" 2>&1"
        ), sound.src, settings.quality, mono_option, sound.temp, sound.log);
  SPDLOG_DEBUG("{}\n", command);
  return command;
}

void encode(const std::string cmd, Media& media) {
  auto sound = media.sound;
  auto settings = media.settings;
  auto use_mono_encoding = (media.args.mono_encoding) ? "In Mono Audio Channel" : "";
  SPDLOG_INFO("Encoding \"{}\" at quality = {} {}\n", sound.src, settings.quality, use_mono_encoding);
  exec(cmd.c_str(), 4096);
}

uintmax_t embed_size(Sound& sound) {
  auto temp   = file_size(sound.src);
  auto image  = file_size(sound.dest);
  auto tag    = sizeof(sound.tag);
  uintmax_t embed_size = temp + image + tag;

  if (temp <= 0) {
    SPDLOG_ERROR("Error: encoding failed");
    throw std::exception();
  } 

  return embed_size;
}

void encodeAudio(Media& media) {
  auto settings = media.settings;

  while (true) {
    encode(format_command(media), media); // Note that doing an initial direct copy in embed would be better
    auto fsize = embed_size(media.sound);
    // If we don't care about the limit
    if (media.args.nolimit)
      break;

    // Else re-encode
    if (fsize < MAX_FILE_POST_SIZE) {
      break;
    } else if (settings.quality > 0) {
        settings.quality -= 6; // Decrease sound quality if file size exceeds our limit
    } else {
      SPDLOG_ERROR("Audio file is too big (>4MiB), try running with -f or --fast\n");
      throw std::exception();
    }
  }
  SPDLOG_INFO("Audio Encoding completed.\n\n");
}

void encodeImage(Media& media) {
  auto sound = media.sound;

  if (!file_exists(sound.src)) { 
    SPDLOG_ERROR("Image or Audio file does not exist or is being blocked");
    remove(sound.temp);
    throw std::exception();
  }

  auto tag = "[" + std::string(sound.tag) + "]";
  append_file(sound.image, sound.dest);
  append_file(sound.temp, sound.dest);
  write_file(sound.dest, tag.c_str(), "a");

  remove(sound.temp);
}

int embed(Media& media) {
  encodeAudio(media);
  encodeImage(media);

  // TODO: Handle cleanup and exceptions here
  return 0;
}

// Extract
std::string find_sound_tag(std::string conts) {
  auto rb = conts.rfind("]"); 
  auto lb = conts.rfind("[");
  if (rb == std::string::npos || lb == std::string::npos) {
    SPDLOG_ERROR("Sound Tag not found.");
    exit(-1);
  }
  auto tag = conts.substr(lb, rb);                  // [audio02] 
  trim(tag);
  auto stripped = tag.substr(1, tag.length() - 2);  // [audio02] => audio02

  SPDLOG_DEBUG("Stripped  : {}", tag);
  SPDLOG_DEBUG("Unstripped: {}", stripped);

  return stripped; 
}

int extract(Media& media) {
  auto msound = media.sound;
  auto imagepath = msound.image;

  SPDLOG_DEBUG("Embedded File Path: {}", msound.image);

  // Sizes of embed file, sound file offset position, sound file
  auto s_embed   = file_size(imagepath);
  auto s_offset  = find_str_offset(imagepath, PNG_ID_FOOTER);
  auto s_oggs    = find_str_offset(imagepath, OGG_ID_HEADER);
  auto s_sound   = file_size(imagepath) + s_offset;

  SPDLOG_DEBUG("Embed File Size    : {}", s_embed);
  SPDLOG_DEBUG("Sound File Size    : {}", s_sound);
  SPDLOG_DEBUG("Image END Offset   : {}", s_offset);
  SPDLOG_DEBUG("Sound START Offset : {}", s_oggs);

  // Note that the file contains embedded null characters
  // The string will get truncated earlier as a result, which is why
  // we specify the filesize
  const char* read = read_file(imagepath);
  std::string embed(read, s_embed);
  std::string image = embed.substr(0, s_offset);
  std::string sound = embed.substr(s_offset, s_embed);
  std::string tag   = find_sound_tag(embed.substr(0, s_oggs)); 

  SPDLOG_DEBUG("Sound Tag Size   : {}", tag);
  tag += ".ogg";

  SPDLOG_INFO("Extracting audio file as \"{}\"\n", tag);

  /** Outputs:
    * sound: audio02.ogg
    * image: image.png.png */

  std::string dest = (msound.dest != nullptr) ? std::string(msound.dest) + "/" : "";
  auto sound_output = dest + tag; 
  auto image_output = dest + std::string(msound.image) + ".png";

  write_file(sound_output.c_str(), sound.c_str(), "w");
  write_file(image_output.c_str(), image.c_str(), "w");

  // Deallocate
  free((void*) read);
  return 0;
}

// Mask
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
