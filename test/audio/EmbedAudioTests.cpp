#include "../doctest-main.cpp"

#include "EmbedAudio.h"
#include "File.h"
#include "Image.h"

using namespace std;
namespace fs = std::filesystem;

string formatCMD(string cmdFormat, Audio::AudioData data) {
    string cmd = fmt::format(cmdFormat, 
      data.audioFile.string(),
      data.audioQuality,
      //data.AudioChannel,
      data.tempAudioFile.string(),
      data.tempLogFile.string()
      );
    return cmd;
}

TEST_CASE("Audio files can be embedded into image files") {
  fs::path imageFile = "../../inputFile1.png.png";
  fs::path audioFile = "";
  ifstream file(imageFile, ifstream::in | ios::binary);

  SUBCASE("Test toLowerCase()") {
    INFO("Current outPut of toLowerCase(): ");

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
    REQUIRE(formatAudioTags(soundTag)[0] == "[audio02]");
    CHECK(!tagUnder100(overflowTag.length()));
  }

  SUBCASE("Ffmpeg cli commands can be built") {
    string legacyCMDFormat = "ffmpeg -y -nostdin -i \"{}\" -vn acodec libvorbis -ar 44100 -aq {} {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1";
    string maskCMDFormat = "ffmpeg -y -nostdin -i \"{}\" -vn acodec libvorbis -aq {} {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1";

    //string audioFilePath = "";
    //string encodedAudioFile = "";
    //Audio::AudioData audioData = { 10, false, "[audio02]", audioFilePath, encodedAudioFile, tempLogFile}; 

    Audio::AudioData audioData = Audio::AudioData("[audio02]", audioFile);
    //REQUIRE(createCommand(audioData, legacyCMDFormat) == formatCMD(legacyCMDFormat, audioData)); 
    //REQUIRE(createCommand(audioData, maskCMDFormat) == formatCMD(maskCMDFormat, audioData)); 

  }

  //embed();
  file.close();
}
