#pragma once

#include "basictypes.h"

namespace cryptagram {

struct Coordinate {
  Coordinate() : w(0), h(0) {}
  Coordinate(int w, int h) : w(w), h(h) {}

  int w;
  int h;
};

} // namespace cryptagram
