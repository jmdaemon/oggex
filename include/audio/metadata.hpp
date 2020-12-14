#ifndef METADATA_HPP 
#define METADATA_HPP

#include <string>

class AudioMetadata {
  private:
    std::string tag;
    int offset, length;
  public:
    AudioMetadata(std::string tag, int offset, int length);

    void setTag(std::string);
    void setOffset(int offset);
    void setLength(int length);
};

#endif
