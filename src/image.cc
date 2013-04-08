#include <cstdio>

#include "image.h"

namespace cryptagram {

Image::Image(int width, int height)
    : width_(width), height_(height) {
  pixel_vals_.reset(new unsigned char[width * height * 3]);
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      for (int i = 0; i < 3; i++) {
        pixel_vals_[h * width * 3 + (3 * w) + i] = 0;
      }
    }
  }
}

Image::~Image() {
}

bool Image::Write(const Coordinate& coord, const RGB& rgb) {
  int index = IndexFromCoordinate(coord);
  pixel_vals_[index] = rgb.r;
  pixel_vals_[index + 1] = rgb.g;
  pixel_vals_[index + 2] = rgb.b;
  return true;
}

int Image::IndexFromCoordinate(const Coordinate& coord) {
  printf("Coord w:%d h:%d\n", coord.w, coord.h);
  int rows = coord.h * width_ * 3;
  int row_col_idx = rows + (coord.w * 3);
  printf("  Index: %d\n", row_col_idx);
  return row_col_idx;
}

} // namespace cryptagram
