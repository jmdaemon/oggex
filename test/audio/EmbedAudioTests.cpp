#include "../doctest-main.cpp"

#include "EmbedAudio.h"
#include "File.h"
#include "Image.h"

#include <fmt/core.h>
#include <fmt/printf.h> 

using namespace std;
namespace fs = std::filesystem;

string formatCMD(string cmdFormat, Audio::AudioData data) {
    string cmd = fmt::format(cmdFormat, 
      data.audioFile.string(),
      data.audioQuality,
      "",
      data.tempAudioFile.string(),
      data.tempLogFile.string()
      );
    return cmd;
}

TEST_CASE("Audio files can be embedded into image files") {
  fs::path embeddedImage  = "../../inputFile1.png";
  fs::path imageFile      = "../../inputFile1.png.png";
  fs::path audioFile      = "../../outputFile1.audio02.ogg";
  ifstream file(embeddedImage, ifstream::in | ios::binary);

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

  SUBCASE("Ffmpeg cli commands are created and formatted correctly") {
    string legacyCMDFormat  = "ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {} {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1";
    string maskCMDFormat    = "ffmpeg -y -nostdin -i \"{}\" -vn acodec libvorbis -aq {} {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1";

    Audio::AudioData audioData = Audio::AudioData("[audio02]", audioFile);
    string legacyCMD  = createCommand(audioData, legacyCMDFormat);
    REQUIRE(!legacyCMD.empty());
    REQUIRE(legacyCMD == formatCMD(legacyCMDFormat, audioData)); 

    string buildLegacyCMD = encodeAudio(audioData);
    string buildMaskCMD   = buildCommand(audioData);

    REQUIRE(buildLegacyCMD == formatCMD(legacyCMD, audioData));
    REQUIRE(buildMaskCMD == formatCMD(maskCMDFormat, audioData));

  }

  SUBCASE("Ffmpeg command executes to completion") {
    Audio::AudioData audioData = Audio::AudioData("[audio02]", audioFile);
    string cmd = encodeAudio(audioData);

    string encodedAudio = exec(cmd.c_str(), audioData);
    REQUIRE(!encodedAudio.empty());
  }

  SUBCASE("Image can be encoded") {
  }


  //embed();
  file.close();
}
