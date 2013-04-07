#pragma once

#include "coordinate.h"
#include "rgb.h"

namespace cryptagram {

class Image {
 public:
  // Constructor for an assumed RGB image that stores three 8-bit values per
  // pixel (one byte per red, green, and blue color channels).
  Image(int width, int height);

  virtual ~Image();

  bool Write(const Coordinate& coord, const RGB& rgb);

  int width();
  int height();

 private:
  int width_;
  int height_;
};

} // namespace cryptagram
