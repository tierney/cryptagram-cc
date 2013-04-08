#pragma once

#include "coordinate.h"
#include "rgb.h"
#include "boost/scoped_array.hpp"

using boost::scoped_array;

namespace cryptagram {

class Image {
 public:
  // Constructor for an assumed RGB image that stores three 8-bit values per
  // pixel (one byte per red, green, and blue color channels).
  Image(int width, int height);

  virtual ~Image();

  bool Write(const Coordinate& coord, const RGB& rgb);

  unsigned char* GetImage() { return pixel_vals_.get(); }
  int GetImageSize() { return width_ * height_ * 3; }

  int width() { return width_; }
  int height() { return height_; }

 private:
  int IndexFromCoordinate(const Coordinate& coord);

  int width_;
  int height_;

  // 3 bytes per pixel ind RGB order. width_ * height_ * 3 values.
  scoped_array<unsigned char> pixel_vals_;
};

} // namespace cryptagram
