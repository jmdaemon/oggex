#include "doctest.h"

#include "EmbedAudio.h"
#include "File.h"
#include "Image.h"
#include "Data.h"

#include <fmt/core.h>

using namespace std;
namespace fs = std::filesystem;

struct DataFixture {
  Audio::AudioData audio;
  Image::ImageData image;
  Options options;
  Data data;
};

std::string formatCommand(Audio::AudioData& audio, bool enableMono) {
  std::string command = (enableMono) ? 
      fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {} -ac 1 -map_metadata -1 \"{}\" >> \"{}\" 2>&1", 
          audio.getAudio().string(), audio.getAudioQuality(), audio.getTempAudio().string(), audio.getTempLog().string()) 
  : 
    fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1", 
          audio.getAudio().string(), audio.getAudioQuality(), audio.getTempAudio().string(), audio.getTempLog().string());
  return command;
}


TEST_CASE("Audio files can be embedded into image files") { 
  const std::string SOUND_TAG = "audio02";
  const std::string AUDIO_FILENAME = "audio02.ogg";
  const std::string IMAGE_FILENAME = "../../inputFile1";
  Audio::AudioData audio = createAudioData(SOUND_TAG, AUDIO_FILENAME);
  Image::ImageData image = Image::ImageData(IMAGE_FILENAME);
  Options options;
  Data data = createEmbedData(audio, image, options);

  fs::path embeddedImage  = "../../inputFile1.png";
  fs::path imageFile      = "../../inputFile2.png";
  fs::path audioFile      = "../../outputFile1.audio02.ogg";
  ifstream file(embeddedImage, ifstream::in | ios::binary);


  //SUBCASE("Ffmpeg command executes to completion") {
    //Audio::AudioData audioData = Audio::AudioData("[audio02]", audioFile);
    //string cmd = encodeAudio(audioData);

    //string encodedAudio = exec(cmd.c_str(), audioData);
    //REQUIRE(!encodedAudio.empty());
  //}

  //SUBCASE("Image can be encoded") {
    //Audio::AudioData audioData = Audio::AudioData("[audio02]", audioFile);
    //string cmd = encodeAudio(audioData);
    //string encodedAudio = exec(cmd.c_str(), audioData);
    //encodeImage(imageFile, encodedAudio, "[audio02]");
    //fs::path outputFilePath = "inputFile2-embed.png";
    //ifstream outputFile(outputFilePath, ifstream::in | ifstream::binary);
    //CHECK(!isCorrupted(outputFilePath, outputFile));
    //outputFile.close();
  //}

  file.close();
}

TEST_CASE("Sound tags should be formatted correctly") {
    string soundTag = "audio02";
    string overflowTag = "====================================================================================================";
    //REQUIRE(tagUnder100(soundTag.length()));
    REQUIRE(formatSoundTag(soundTag) == "[audio02]");
    //CHECK(!tagUnder100(overflowTag.length()));
}

TEST_CASE("Capitalized file extensions should be converted to lowercase") {
  INFO("Current output of toLowerCase(): ");
  REQUIRE(File::toLowerCase("ABC") == "abc");
  REQUIRE(File::toLowerCase(".JPG") == ".jpg");
  CHECK(File::toLowerCase(".JPEG") == ".jpeg");
  CHECK(File::toLowerCase(".PNG") == ".png");
}


TEST_CASE("Clean should remove temporary files") {
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

TEST_CASE_FIXTURE(DataFixture, "Ffmpeg command should execute without any problems") { }

TEST_CASE_FIXTURE(DataFixture, "EncodeAudio function should create a temp.ogg file") { }

TEST_CASE_FIXTURE(DataFixture, "EncodeImage function should create an [image]-embed.png file") { }
