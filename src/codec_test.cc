#include "image.h"
#include "codec.h"
#include "gtest/gtest.h"
#include "boost/scoped_array.hpp"

using boost::scoped_array;

namespace cryptagram {

class CodecTest : public testing::Test {
 protected:
};


TEST_F(CodecTest, Basic) {
  cryptagram::Image img(0, 0);

  cryptagram::Codec codec(&img);

  codec.Write(1);
}

TEST_F(CodecTest, UpdateNext) {
  cryptagram::Image img(0, 0);

  cryptagram::Codec codec(&img);

  codec.UpdateNext();

}

} // namespace cryptagram
