#include "image.h"
#include "cryptagram.h"
#include "gtest/gtest.h"
#include "boost/scoped_array.hpp"

using boost::scoped_array;
using std::string;

namespace cryptagram {

class CryptagramTest : public testing::Test {
 protected:
};


TEST_F(CryptagramTest, Basic) {
  int width = 10;
  int height = 10;
  cryptagram::Image img(width, height);
  unsigned char* res = img.GetImage();
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      for (int i = 0; i < 3; i++) {
        printf("%3d ", res[(h * width * 3)+ (3 * w) + i]);
      }
      printf(". ");
    }
    printf("\n");
  }

  cryptagram::Codec codec(&img);

  cryptagram::Cryptagram cryptagram(&codec);

  string input("abc");
  cryptagram.Write(input);
  res = img.GetImage();
  printf("\n");
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      for (int i = 0; i < 3; i++) {
        printf("%3d ", res[(h * width * 3) + (3 * w) + i]);
      }
      printf(". ");
    }
    printf("\n");
  }
}

} // namespace cryptagram
