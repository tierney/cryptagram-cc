#include "image.h"

namespace cryptagram {

Image::Image(int width, int height) : width_(width), height_(height) {
  pixel_vals_ = new unsigned char[width * height * 3];
}

Image::~Image() {
}

bool Image::Write(const Coordinate& coord, const RGB& rgb) {
  int index = IndexFromCoordinate(coord);
  pixel_vals_[index] = rgb.r;
  pixel_vals_[index] = rgb.g;
  pixel_vals_[index] = rgb.b;
  return true;
}

int Image::IndexFromCoordinate(const Coordinate& coord) {
  int rows = coord.h * width_ * 3;
  int row_col_idx = rows + coord.w;
  return row_col_idx;
}

} // namespace cryptagram
