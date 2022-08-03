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
  //auto sizeWithUnit = formatBytes(data, std::get<1>(sizeTuple)); 
  //auto sizeWithUnit = formatBytes(data, std::get<1>(sizeTuple)); 
  Byte to  = formatBytes(data, std::get<1>(sizeTuple)); 
  //sizewithUnit = convert_units();
  rightPadding = (!data.options.isReadableEnabled()) ? 8 : 4;
  //fmt::print("{:<{}} : {:<{}} {}\n", std::get<0>(sizeTuple), leftPadding, std::get<0>(sizeWithUnit), rightPadding, std::get<1>(sizeWithUnit));
  char* amt;
  //mpfr_get_str(amt, 10, int, size_t, mpfr_srcptr, mpfr_rnd_t)
  mpfr_asprintf(&amt, "%Rf", to.amt);
  fmt::print("{:<{}} : {:<{}} {}\n", std::get<0>(sizeTuple), leftPadding, amt, rightPadding, to.unit);
  /* Deallocate */
  mpfr_clears(to.amt, NULL);
  mpfr_free_cache2(MPFR_FREE_LOCAL_CACHE);
}

Byte formatBytes(Data& data, size_t bytes, unsigned int decimals) {
//std::tuple<std::string, std::string> formatBytes(Data& data, size_t bytes, unsigned int decimals) {
  Byte to;
  if (!data.options.isReadableEnabled())
    // If we don't care about the format, return bytes
    //return std::make_tuple(bytes, "B");
    //return ByteFormat { byteToString(bytes), "B" };
    {
      mpfr_init2(to.amt, 200);
      mpfr_init_set_str(to.amt, std::to_string(bytes).c_str(), 10, MPFR_RNDF);
      std::string units_to = "B";
      const char* units_to_cstr = units_to.c_str();
      to.unit = const_cast<char*> (units_to_cstr);
      return to;
    }

  // Automatically convert the bytes into a more readable format
  unsigned int scale = (data.options.isSIEnabled()) ? SI_SCALE : BINARY_SCALE;

  mpfr_t amt;
  mpfr_init2(amt, 200);
  mpfr_init_set_str(amt, std::to_string(bytes).c_str(), 10, MPFR_RNDF);
  to = auto_size(amt, scale, true);

  //unsigned long int output = mpfr_get_ui (to.amt, MPFR_RNDD);
  size_t output = mpfr_get_ui (to.amt, MPFR_RNDF);
  std::string unit(to.unit);
  
  /* Deallocate */
  //mpfr_clears(to.amt, NULL);
  mpfr_clears(amt, NULL);
  mpfr_free_cache2(MPFR_FREE_LOCAL_CACHE);
  return to;

  //return std::make_tuple(output, unit);
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
