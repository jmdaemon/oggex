#include "Data.h"

Data createEmbedData(Audio::AudioData audio, const char* image, Options options) { 
  return Data{ .audio = audio, .image = image, .options = options};
}

Data createExtractData(const char* image, Options options) {
  return Data{ .image = image, .options = options};
}

void printSize(std::string key, std::string value, unsigned int leftPadding, unsigned int rightPadding) { 
  fmt::print("{:<{}} : {:<{}}\n", key, leftPadding, value, rightPadding);
}

void printSize(Data& data, std::tuple<std::string, size_t> sizeTuple, unsigned int leftPadding, unsigned int rightPadding) { 
  Byte to;
  std::string bytes = std::to_string(std::get<1>(sizeTuple));
  const char* bstr = bytes.c_str();
  if (!data.options.isReadableEnabled()) {
    // If we don't care about the format, return bytes
    const char* units = "B";
    to = convert_units(bstr, units, units);
  } else {
    // Automatically convert the bytes into a more readable format
    unsigned int scale = (data.options.isSIEnabled()) ? SI_SCALE : BINARY_SCALE;
    to = auto_format_bstr(bstr, scale);
  }

  rightPadding = (!data.options.isReadableEnabled()) ? 8 : 4;
  const unsigned long int amt = mpfr_get_ui (to.amt, MPFR_RNDF);
  const std::string unit(to.unit);

  fmt::print("{:<{}} : {:<{}} {}\n", std::get<0>(sizeTuple), leftPadding, amt, rightPadding, unit);
  /* Deallocate */
  mpfr_clears(to.amt, NULL);
  mpfr_free_cache2(MPFR_FREE_LOCAL_CACHE);
}

void printEmbedSizes(Data& data, size_t maxFileSize, size_t tempFileSize, size_t imageFileSize, size_t soundTagSize, size_t finalSize) {
    std::map<int, std::tuple<std::string, size_t>> sizes = {
      { 0, std::make_tuple("Max File Size"  , maxFileSize)},
      { 1, std::make_tuple("Temp File Size" , tempFileSize)},
      { 2, std::make_tuple("Image File Size", imageFileSize)},
      { 3, std::make_tuple("Sound Tag Size" , soundTagSize)},
      { 4, std::make_tuple("Final Size"     , finalSize)}
    };

    fmt::print("\n================ File Sizes ================\n");
    for (auto const& [key, sizeTuple] : sizes)
      printSize(data, sizeTuple, 16); 
}

void printExtractSizes(Data& data, size_t embeddedFileSize, size_t audioFileSize, size_t audioOffset) {
  std::map<int, std::tuple<std::string, size_t>> sizes = {
      { 0, std::make_tuple("Size of Embedded File"  , embeddedFileSize)},
      { 1, std::make_tuple("Audio File Size"        , audioFileSize)},
      { 2, std::make_tuple("Audio File Offset"      , audioOffset)}
    };

    fmt::print("\n================ File Sizes ================\n"); 
    for (auto const& [key, sizeTuple] : sizes)
      printSize(data, sizeTuple, 24); 
}
