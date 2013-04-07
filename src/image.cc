#include "image.h"

namespace cryptagram {

Image::Image(int width, int height) : width_(width), height_(height) {
}

Image::~Image() {
}

bool Image::Write(const Coordinate& coord, const RGB& rgb) {
  return true;
}

} // namespace cryptagram
