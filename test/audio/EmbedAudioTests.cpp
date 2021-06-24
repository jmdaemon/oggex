#include "doctest.h"

#include "EmbedAudio.h"
#include "File.h"
#include "Image.h"
#include "Data.h"

#include <fmt/core.h>

using namespace std;
namespace fs = std::filesystem;

struct DataFixture {
  const std::string SOUND_TAG       = "audio02";
  const std::string AUDIO_FILENAME  = "../../outputFile1.audio02.ogg";
  const std::string IMAGE_FILENAME  = "../../inputFile1";

  Audio::AudioData audio{};
  Image::ImageData image{};
  Options options;
  Data data{};

  DataFixture() : audio(createAudioData(SOUND_TAG, AUDIO_FILENAME)), 
  image(Image::ImageData(IMAGE_FILENAME)), data(createEmbedData(audio, image, options)) { }
};

std::string formatCommand(Audio::AudioData& audio, bool enableMono) {
  std::string command = ((enableMono) ? 
      fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {} -ac 1 -map_metadata -1 \"{}\" >> \"{}\" 2>&1", 
          audio.getAudio().string(), audio.getAudioQuality(), audio.getTempAudio().string(), audio.getTempLog().string()) 
  : 
    fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1", 
          audio.getAudio().string(), audio.getAudioQuality(), audio.getTempAudio().string(), audio.getTempLog().string()));
  return command;
}

TEST_CASE("Clean should remove temporary files") { 
  ofstream testFile("Test.txt");
  testFile << "clean() should remove this file.";
  testFile.close();

  REQUIRE(std::filesystem::exists("Test.txt"));
  clean({ "Test.txt" });
  REQUIRE(!std::filesystem::exists("Test.txt"));
}

TEST_CASE_FIXTURE(DataFixture, "Ffmpeg CLI commands are created and formatted correctly") {
    //string legacyCMDFormat  = "ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1";
    //string maskCMDFormat    = "ffmpeg -y -nostdin -i \"{}\" -vn acodec libvorbis -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1";
    data.options.enableMono(true);
    string monoAudioCommand = createCommand(data);
    string properMonoAudioCommand = formatCommand(audio, data.options.isMonoEnabled());

    data.options.enableMono(false);
    string dualAudioCommand = createCommand(data);
    string properDualAudioCommand = formatCommand(audio, data.options.isMonoEnabled());
    
    REQUIRE(monoAudioCommand == properMonoAudioCommand); 
    REQUIRE(properDualAudioCommand == properDualAudioCommand);
}

TEST_CASE_FIXTURE(DataFixture, "Exec run and execute ffmpeg commands") { 
  const std::string command = formatCommand(audio, data.options.isMonoEnabled());
  std::string output = exec(command, data);
  REQUIRE(!output.empty());
} 

TEST_CASE_FIXTURE(DataFixture, "Audio files can be embedded into image files") {
  // Encode Audio properly executes ffmpeg command and creates the "temp.ogg" intermediary file

  INFO("EncodeAudio function should create a temp.ogg file");
  // Encode Audio with default settings
  data.options.enableMono(true);
  REQUIRE(!encodeAudio(data).empty());
  REQUIRE(std::filesystem::exists("temp.ogg"));
  clean({"temp.ogg"});

  // Disable mono audio channel, and ignore the 4MiB Limit
  data.options.enableMono(false);
  data.options.ignoreLimit(true);
  REQUIRE(!encodeAudio(data).empty());
  REQUIRE(std::filesystem::exists(data.audio.getTempAudio()));
  clean({data.audio.getTempAudio()});

  INFO("EncodeImage function should create an [image]-embed.png file");
  // Ensure that the embedded output file is created
  CHECK_THROWS_AS(encodeImage(data), const std::exception&); 
  encodeAudio(data, data.options.isMonoEnabled());
  encodeImage(data);
} 
