#include "codec.h"
#include "map-util.h"
#include "glog/logging.h"

namespace cryptagram {

Codec::Codec(Image* img) : img_(img) {
  val_to_rgb_[0] = 0;
  val_to_rgb_[1] = 255;
}

Codec::~Codec() {
}

bool Codec::Write(const int bits) {
  const RGB* rgb = FindOrNull(val_to_rgb_, bits);
  if (rgb) {
    img_->Write(Coordinate(cur_w, cur_h), *rgb);

    UpdateNext();

    return true;
  }
  return false;
}

void Codec::UpdateNext() {
  Coordinate coord;
  Next(&coord);
  cur_w = coord.w;
  cur_h = coord.h;
}

void Codec::Next(Coordinate* coord) {
  CHECK_NOTNULL(coord);
  if (cur_w + 1 >= img_->width()) {
    // Reset width and increment height.
    coord->h = cur_h + 1;

    if (cur_h <= kSpecialThreshold) {
      coord->w = kFirstColumnAfterHeader;
    }
  } else {
    coord->w = cur_w + 1;
  }
}

} // namespace cryptagram
