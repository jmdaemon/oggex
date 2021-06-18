#include "doctest.h"

#include "EmbedAudio.h"
#include "File.h"
#include "Image.h"
#include "Data.h"

#include <fmt/core.h>
//#include <fmt/printf.h> 
//#include <fmt/format.h>

using namespace std;
namespace fs = std::filesystem;

//string formatCMD(Audio::AudioData data, string cmdFormat = "NA") {
    //string cmd = fmt::format(cmdFormat, 
      //data.audioFile.string(),
      //data.audioQuality,
      //"",
      //data.tempAudioFile.string(),
      //data.tempLogFile.string()
      //);
    //return cmd;
//}

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

  SUBCASE("Test toLowerCase()") {
    INFO("Current output of toLowerCase(): ");

    REQUIRE(File::toLowerCase("ABC") == "abc");
    REQUIRE(File::toLowerCase(".JPG") == ".jpg");
    CHECK(File::toLowerCase(".JPEG") == ".jpeg");
    CHECK(File::toLowerCase(".PNG") == ".png");
  }
  SUBCASE("Temp files should be removed") {
  }

  SUBCASE("Sound tags should be formatted correctly") {
    string soundTag = "audio02";
    string overflowTag = "====================================================================================================";
    REQUIRE(tagUnder100(soundTag.length()));
    REQUIRE(formatSoundTag(soundTag) == "[audio02]");
    CHECK(!tagUnder100(overflowTag.length()));
  }

  SUBCASE("Ffmpeg cli commands are created and formatted correctly") {
    string legacyCMDFormat  = "ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1";
    string maskCMDFormat    = "ffmpeg -y -nostdin -i \"{}\" -vn acodec libvorbis -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1";


    //Audio::AudioData audio = Audio::AudioData("audio02", audioFile);
    data.options.enableMono(true);
    string monoAudioCommand = createCommand(data);

    //data.options.enableMono(false);
    //string modernCommand = createCommand(data);

    string properMonoCommand = "";
      //fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {} -ac 1 -map_metadata -1 \"{}\" >> \"{}\" 2>&1", 
          //audio.getAudio(), audio.getAudioQuality(), audio.getTempAudio(), audio.getTempLog());

    //string properLegacyCommand = 
      //fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {} -ac 1 -map_metadata -1 \"{}\" >> \"{}\" 2>&1";
          //audio.getAudio(), audio.getAudioQuality(), audio.getTempAudio(), audio.getTempLog());


    //string legacyCMD  = createCommand(audioData, legacyCMDFormat);
    //REQUIRE(!legacyCMD.empty());
    //REQUIRE(legacyCMD == formatCMD(legacyCMDFormat, audioData)); 
    REQUIRE(monoAudioCommand == properMonoCommand); 

    //string buildLegacyCMD = encodeAudio(audioData);
    //string buildMaskCMD   = buildCommand(audioData);

    //REQUIRE(buildLegacyCMD == formatCMD(legacyCMD, audioData));
    //REQUIRE(buildMaskCMD == formatCMD(maskCMDFormat, audioData));

  }

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
