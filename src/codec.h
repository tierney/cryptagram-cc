#pragma once

#include <map>

#include "basictypes.h"
#include "image.h"
#include "rgb.h"

#include "gtest/gtest_prod.h"

namespace cryptagram {

const int kSpecialThreshold = 8; // For the header block, we need to not write
                                 // in the first columns of kSpecialThreshold
                                 // rows.
const int kFirstColumnAfterHeader = 8;

class Codec {
 public:
  explicit Codec(Image* img);

  virtual ~Codec();

  bool Write(const int bits);

 private:
  FRIEND_TEST(CodecTest, UpdateNext);

  void UpdateNext();
  void Next(Coordinate* coord);

  Image* img_;

  std::map<int, RGB> val_to_rgb_;

  int cur_w;
  int cur_h;
};

} // namespace cryptagram
