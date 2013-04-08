#pragma once

#include <map>

#include "basictypes.h"
#include "image.h"
#include "rgb.h"

#include "gtest/gtest_prod.h"

using std::map;

namespace cryptagram {

const int kFirstRowAfterHeader = 8; // For the header block, we need to not
                                    // write in the first columns of
                                    // kFirstRowAfterHeader rows.

const int kFirstColumnAfterHeader = 8;

class Codec {
 public:
  // Does not take ownership of img.
  explicit Codec(Image* img);

  virtual ~Codec();

  bool Write(const int bits);

 private:
  FRIEND_TEST(CodecTest, UpdateNext);

  void UpdateNext();
  void Next(Coordinate* coord);

  Image* img_;

  map<int, RGB> val_to_rgb_;

  int cur_w_;
  int cur_h_;

  DISALLOW_COPY_AND_ASSIGN(Codec);
};

} // namespace cryptagram
