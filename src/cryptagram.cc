#include "cryptagram.h"

#include <cstdio>

namespace cryptagram {

const int kBitsInByte = 8;

Cryptagram::Cryptagram(Codec* codec) : codec_(codec) {
}

Cryptagram::~Cryptagram() {
}

bool Cryptagram::Write(const string& input) {
  for (int i = 0; i < input.size(); i++) {
    std::cout << input[i] << " <--" << std::endl;
    for (int j = 0; j < kBitsInByte; j++) {
      int is_set = input[i] & (1 << j);
      // printf("Writing: %d\n", is_set);
      if (!codec_->Write(is_set)) {
        std::cerr << "Problem with " << i << " " << j << " " << is_set
                  << std::endl;
      }
    }
  }
  return true;
}

} // namespace cryptagram
