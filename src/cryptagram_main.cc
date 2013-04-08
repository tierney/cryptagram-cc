#include <iostream>
#include <fstream>
#include <cmath>

#include "cryptagram.h"
#include "codec.h"
#include "image.h"
#include "glog/logging.h"
#include "google/gflags.h"
#include "jpeg_codec.h"

DEFINE_string(msg, "", "Message to embed.");
DEFINE_double(width_to_height_ratio, 1.0, "Width to height ratio.");

using gfx::JPEGCodec;
using std::ofstream;
using std::ios;

namespace {

int ceil(int numerator, int denominator) {
  return (numerator + denominator - 1) / denominator;
}

} // namespace

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, false);

  std::cout << FLAGS_msg.length() << std::endl;
  int msg_len = FLAGS_msg.length();

  // Given data length and aspect ratio, estimate the needed image.
  int min_pixels = 64 + (8 * msg_len);
  int height = sqrt(min_pixels / FLAGS_width_to_height_ratio) + 1;
  int width = ceil(min_pixels, height);
  std::cout << "Pix: " << min_pixels << std::endl;
  std::cout << "Trying " << width << " " << height << std::endl;

  // Image dimensions.
  cryptagram::Image img(width, height);
  cryptagram::Codec codec(&img);
  cryptagram::Cryptagram cryptagram(&codec);
  cryptagram.Write(FLAGS_msg);

  unsigned char* res = img.GetImage();

  // Write the image.
  std::vector<unsigned char> output;
  JPEGCodec::Encode(res, JPEGCodec::FORMAT_RGB, width, height,
                    width * 3, 100, &output);
  ofstream outfile("test.jpg", std::ofstream::binary);
  outfile.write((char *)&output[0], output.size());
  return 0;
}
