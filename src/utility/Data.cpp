#include "Data.h"

Data createEmbedData(Audio::AudioData audio, Image::ImageData image, Options options) { 
  return Data{ .audio = audio, .image = image, .options = options};
}

Data createExtractData(Image::ImageData image, Options options) {
  return Data{ .image = image, .options = options};
}

template<typename T>
std::string byteToString(T bytes, unsigned int dm = 10) {
    std::stringstream ss; 
    ss.precision(dm); 
    ss << bytes; 
    std::string byteString = ss.str();
    return byteString;
}

void printSize(std::string key, std::string value, unsigned int leftPadding, unsigned int rightPadding) { 
  fmt::print("{:<{}} : {:<{}}\n", key, leftPadding, value, rightPadding);
}

void printSize(Data& data, std::tuple<std::string, size_t> sizeTuple, unsigned int leftPadding, unsigned int rightPadding) { 
  //Byte to = formatBytes(data, std::get<1>(sizeTuple)); 
  Byte to;
  //size_t numbytes = std::get<1>(sizeTuple);
  std::string bytes = std::to_string(std::get<1>(sizeTuple));
  const char* bstr = bytes.c_str();
  //size_t bytes = std::get<1>(sizeTuple);
  //const char* bytes = std::to_string(numbytes).c_str();
  if (!data.options.isReadableEnabled()) {
    const char* units = "B";
    to = convert_units(bstr, units, units);
  } else {
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

//Byte formatBytes(Data& data, size_t bytes) {
  //Byte to;
  //if (!data.options.isReadableEnabled()) {
    //const char* units = "B";
    //to = convert_units(std::to_string(bytes).c_str(), units, units);
  //}

  //// Automatically convert the bytes into a more readable format
  //unsigned int scale = (data.options.isSIEnabled()) ? SI_SCALE : BINARY_SCALE;

  //mpfr_t amt;
  //mpfr_init2(amt, 200);
  //mpfr_init_set_str(amt, std::to_string(bytes).c_str(), 10, MPFR_RNDF);
  //to = auto_size(amt, scale, true);

  //[> Deallocate <]
  //mpfr_clears(amt, NULL);
  //mpfr_free_cache2(MPFR_FREE_LOCAL_CACHE);
  //return to;
//}

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
