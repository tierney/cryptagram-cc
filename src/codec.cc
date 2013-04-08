#include "codec.h"
#include "map-util.h"
#include "glog/logging.h"

using std::make_pair;

namespace cryptagram {

Codec::Codec(Image* img) : img_(img), cur_w_(8), cur_h_(0) {
  val_to_rgb_.insert(make_pair(0, RGB(0,0,0)));
  val_to_rgb_.insert(make_pair(1, RGB(255,255,255)));
}

Codec::~Codec() {
}

bool Codec::Write(const int bits) {
  int interpreted = 0 ? bits <= 0 : 1;
  const RGB* rgb = FindOrNull(val_to_rgb_, interpreted);
  if (rgb) {
    img_->Write(Coordinate(cur_w_, cur_h_), *rgb);

    UpdateNext();

    return true;
  }
  return false;
}

void Codec::UpdateNext() {
  Coordinate coord;
  Next(&coord);
  cur_w_ = coord.w;
  cur_h_ = coord.h;
}

void Codec::Next(Coordinate* coord) {
  CHECK_NOTNULL(coord);
  if (cur_w_ + 1 >= img_->width()) {
    // Reset width and increment height.
    coord->h = cur_h_ + 1;

    if (cur_h_ <= kSpecialThreshold) {
      coord->w = kFirstColumnAfterHeader;
    }
  } else {
    coord->w = cur_w_ + 1;
  }
}

} // namespace cryptagram
