#pragma once

#include <string>
#include "codec.h"

using std::string;

namespace cryptagram {

class Cryptagram {
 public:
  // Does not take ownership of codec.
  explicit Cryptagram(Codec* codec);

  virtual ~Cryptagram();

  // Assumes that input is composed of one byte chars. Current implementation
  // assumes that the codec just needs one bit value from the input to write the
  // value to the underlying image.
  bool Write(const string& input);

 private:
  Codec* codec_;

};

} // namespace cryptagram
