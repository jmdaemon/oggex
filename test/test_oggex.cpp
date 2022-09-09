#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "oggex.h"
#include <unistd.h>
#include <limits.h>
#include <cstdarg>
//#include <pthread.h>
#include <filesystem>
#include <thread>

// Samples
const static std::string AUDIO_FILE = "audio02.ogg";
const static std::string IMAGE_FILE = "835127a09fc542aeb3bfa99c9d91972d.png.png";
const static std::string EMBED_FILE = "835127a09fc542aeb3bfa99c9d91972d.png";
const static std::string SOUND_TAG  = "audio02";

// Helper Functions

std::string formatPath(const char* cwd, const std::string path) {
  return fmt::format("{}/{}", cwd, path);
}

std::string fmtEmbedCommand(std::string command, std::string audio, std::string image, std::string tag) {
  return fmt::format("{} embed -a {} -i {} -t {}", command, audio, image, tag);
}

std::string fmtExtractCommand(std::string command, std::string embed) {
  return fmt::format("{} extract -i {}", command, embed);
}

void run_embed_test(std::string bin, std::string audio, std::string image, std::string tag, std::string embed) {
    auto command = fmtEmbedCommand(bin, audio, image, tag);
    fmt::print("{}\n", command);

    system(command.c_str());
    //std::thread run_cmd(system, command.c_str());
    //run_cmd.join();

    const char* embed_cstr = embed.c_str();
    bool result = std::filesystem::exists(embed_cstr);
    CHECK(result != false);
    remove(embed_cstr);
}

/** Clean the teest output files */
void clean_test(const char* path, ...) {
    va_list args;
    va_start(args, path);
    while (*path != '\0') {
      remove(path);
    }
    va_end(args);
}

// Integration Tests
TEST_CASE("Test File Embedding") {
  fmt::print("Test File Embedding\n");
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));
  fmt::print("Current Directory: {}\n", cwd);

  chdir("./samples/embed");
  getcwd(cwd, sizeof(cwd));
  fmt::print("Current Directory: {}\n", cwd);
  
  auto audio  = formatPath(cwd, AUDIO_FILE);
  auto image  = formatPath(cwd, IMAGE_FILE);
  auto embed  = formatPath(cwd, EMBED_FILE);
  auto tag    = SOUND_TAG;

  if (audio.empty() || image.empty() || embed.empty() || tag.empty()) {
    fmt::print("Cannot execute embed tests. Exiting.\n");
    exit(-1);
  }
  
  SUBCASE("oggex embed") {
    auto bin = "../../app/oggex";
    run_embed_test(bin, audio, image, tag, embed);
  }

  SUBCASE("oggex-gtk embed") {
    auto bin = "../../app/gtk/src/oggex-gtk";
    run_embed_test(bin, audio, image, tag, embed);
  }

  SUBCASE("oggex-qt embed") {
    auto bin = "../../app/qt/oggex-qt";
    run_embed_test(bin, audio, image, tag, embed);
  }
}

TEST_CASE("File Extract Tests") {
  // Working directory
  //system("cd samples/extract");
  char cwd[PATH_MAX];
  fmt::print("Test File Extract\n");

  getcwd(cwd, sizeof(cwd));
  fmt::print("Current Directory: {}\n", cwd);

  chdir("samples/extract");
  getcwd(cwd, sizeof(cwd));
  fmt::print("Current Directory: {}\n", cwd);
  
  auto audio  = formatPath(cwd, AUDIO_FILE);
  auto image  = formatPath(cwd, IMAGE_FILE);
  auto embed  = formatPath(cwd, EMBED_FILE);
  auto tag    = SOUND_TAG;
  /*

  SUBCASE("oggex extract") {
    auto bin = "../../app/oggex";
    auto command = fmtExtractCommand(bin, embed);
    fmt::print("{}", command);

    //system(command.c_str());

    //pthread_t thread_id;
    //pthread_create(&thread_id, NULL, system, command.c_str());
    std::thread run_cmd(system, command.c_str());
    run_cmd.join();
    //pthread_join(thread_id, NULL);

    CHECK(file_exists(audio.c_str()));
    CHECK(file_exists(image.c_str()));
    clean_test(audio.c_str(), image.c_str());
  }
  */

  /*
  SUBCASE("oggex-gtk extract") {
    auto bin = "../../app/gtk/src/oggex-gtk";
    auto command = fmtExtractCommand(bin, embed);
    fmt::print("{}", command);
    system(command.c_str());

    CHECK(file_exists(audio.c_str()));
    CHECK(file_exists(image.c_str()));
    clean_test(audio.c_str(), image.c_str());
  }

  SUBCASE("oggex-qt extract") {
    auto bin = "../../app/qt/oggex-qt";
    auto command = fmtExtractCommand(bin, embed);
    fmt::print("{}", command);
    system(command.c_str());

    CHECK(file_exists(audio.c_str()));
    CHECK(file_exists(image.c_str()));
    clean_test(audio.c_str(), image.c_str());
  }
  */
}

/**
  * TODO:
  * Tests needing to be written:
  * - dataToString
  * - format_command
  * - embed_size
  * - encode/encodeAudio
  * - encodeImage
  * - getOffset
  * - findSoundTag
  * - extract
  */

// Tests:
//TEST_CASE("") { 
//}


//const static struct Sample samples = {
  //AUDIO_FILE, IMAGE_FILE, EMBED_FILE, SOUND_TAG
//};

//struct DataFixture {
  //const std::string SOUND_TAG       = "audio02";
  //const std::string AUDIO_FILENAME  = "../../outputFile1.audio02.ogg";
  //const std::string IMAGE_FILENAME  = "../../inputFile2.png";

  //Audio::AudioData audio{};
  ////Image::ImageData image{};
  //const char* image{};
  //Options options;
  //Data data{};

  //DataFixture() : audio(createAudioData(SOUND_TAG, AUDIO_FILENAME)), 
  ////image(Image::ImageData(IMAGE_FILENAME)), data(createEmbedData(audio, image, options)) { }
  //image(IMAGE_FILENAME.c_str()), data(createEmbedData(audio, image, options)) { }
//};

//std::string formatCommand(Audio::AudioData& audio, bool enableMono) {
  //std::string command = ((enableMono) ? 
      //fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {} -ac 1 -map_metadata -1 \"{}\" >> \"{}\" 2>&1", 
          //audio.getAudio().string(), audio.getAudioQuality(), audio.getTempAudio().string(), audio.getTempLog().string()) 
  //: 
    //fmt::format("ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {} -map_metadata -1 \"{}\" >> \"{}\" 2>&1", 
          //audio.getAudio().string(), audio.getAudioQuality(), audio.getTempAudio().string(), audio.getTempLog().string()));
  //return command;
//}

//TEST_CASE("Clean should remove temporary files") { 
  //std::ofstream testFile("Test.txt");
  //testFile << "clean() should remove this file.";
  //testFile.close();

  //REQUIRE(std::filesystem::exists("Test.txt"));
  //clean({ "Test.txt" });
  //REQUIRE(!std::filesystem::exists("Test.txt"));
//}

//TEST_CASE_FIXTURE(DataFixture, "Ffmpeg CLI commands are created and formatted correctly") {
    ////string legacyCMDFormat  = "ffmpeg -y -nostdin -i \"{}\" -vn -codec:a libvorbis -ar 44100 -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1";
    ////string maskCMDFormat    = "ffmpeg -y -nostdin -i \"{}\" -vn acodec libvorbis -aq {}{} -map_metadata -1 \"{}\" >> \"{}\" 2>&1";
    //data.options.enableMono(true);
    //auto monoAudioCommand = createCommand(data);
    //auto properMonoAudioCommand = formatCommand(audio, data.options.isMonoEnabled());

    //data.options.enableMono(false);
    //auto dualAudioCommand = createCommand(data);
    //auto properDualAudioCommand = formatCommand(audio, data.options.isMonoEnabled());
    
    //REQUIRE(monoAudioCommand == properMonoAudioCommand); 
    //REQUIRE(properDualAudioCommand == properDualAudioCommand);
//}

//TEST_CASE_FIXTURE(DataFixture, "Exec run and execute ffmpeg commands") { 
  //const std::string command = formatCommand(audio, data.options.isMonoEnabled());
  //std::string output = exec(command, data);
  //REQUIRE(!output.empty());
//} 

//TEST_CASE_FIXTURE(DataFixture, "Audio files can be embedded into image files") {
  //// Encode Audio properly executes ffmpeg command and creates the "temp.ogg" intermediary file

  //INFO("EncodeAudio function should create a temp.ogg file");
  //// Encode Audio with default settings
  //data.options.enableMono(true);
  //REQUIRE(!encodeAudio(data).empty());
  //REQUIRE(std::filesystem::exists("temp.ogg"));
  ////clean({"temp.ogg"});
  //remove("temp.ogg");

  //// Disable mono audio channel, and ignore the 4MiB Limit
  //data.options.enableMono(false);
  //data.options.ignoreLimit(true);
  //REQUIRE(!encodeAudio(data).empty());
  //REQUIRE(std::filesystem::exists(data.audio.getTempAudio()));
  ////clean({data.audio.getTempAudio()});
  //remove(data.audio.getTempAudio());

  //INFO("EncodeImage function should create an [image]-embed.png file");
  //// Ensure that the embedded output file is created
  //CHECK_THROWS_AS(encodeImage(data), const std::exception&); 
  //encodeAudio(data, data.options.isMonoEnabled());
  //encodeImage(data);
//} 

// Oggex Extract Audio Tests
//struct DataFixture {
  //const std::string EMBEDDED_FILENAME  = "../../inputFile1.png";

  //Image::ImageData image{};
  //Options options;
  //Data data{};

  //DataFixture() : image(Image::ImageData(EMBEDDED_FILENAME)), data(createExtractData(image, options)) { }
//};


//TEST_CASE_FIXTURE(DataFixture, "getOffset()") {
  //size_t offset = getOffset(EMBEDDED_FILENAME);
  //REQUIRE(offset != 0);

  //offset = getOffset("SearchTermUnavailable");
  //REQUIRE(offset == 0);
//}

//TEST_CASE_FIXTURE(DataFixture, "findSoundTag should return sound tag in embedded file") { 
  //std::filesystem::path image = data.image.getImage();
  //string embeddedFileData   = dataToString(image, 0);
  //size_t audioOffset        = getOffset(image);
  //std::string soundTag      = findSoundTag(data, embeddedFileData, audioOffset);
  //REQUIRE(!soundTag.empty());
  //embeddedFileData          = dataToString(image, sizeOf(image));
  //soundTag                  = findSoundTag(data, embeddedFileData, sizeOf(image));
  //REQUIRE(soundTag.empty());
//}

//TEST_CASE_FIXTURE(DataFixture, "extract()") { 
  //REQUIRE(extract(data) == 0);
//}
