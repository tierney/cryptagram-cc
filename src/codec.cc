#include "codec.h"
#include "map-util.h"

namespace cryptagram {

Codec::Codec(Image* img) : img_(img) {
}

bool Codec::Write(const int bits) {
  const RGB* rgb = FindOrNull(val_to_rgb_, bits);
  if (rgb) {
    img_->Write(this->Next(), *rgb);

    UpdateNext();

    return true;
  }
  return false;
}

void Codec::UpdateNext() {
  if (cur_w + 1 >= img_->width()) {
    // Reset width and increment height.
    cur_h++;

    if (cur_h <= kSpecialThreshold) {
      cur_w = kFirstColumnAfterHeader;
    }
  } else {
    cur_w++;
  }
}

} // namespace cryptagram
