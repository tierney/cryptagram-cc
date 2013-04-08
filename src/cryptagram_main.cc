#include <iostream>
#include <fstream>

#include "cryptagram.h"
#include "codec.h"
#include "image.h"
#include "glog/logging.h"
#include "google/gflags.h"
#include "jpeg_codec.h"

DEFINE_string(msg, "", "Message to embed.");

using gfx::JPEGCodec;
using std::ofstream;
using std::ios;

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, false);

  std::cout << FLAGS_msg.length();
  int msg_len = FLAGS_msg.length();
  int width = 8 + 8 * msg_len;
  int height = 8;

  cryptagram::Image img(width, height);
  cryptagram::Codec codec(&img);
  cryptagram::Cryptagram cryptagram(&codec);
  cryptagram.Write(FLAGS_msg);

  unsigned char* res = img.GetImage();

  std::vector<unsigned char> output;
  JPEGCodec::Encode(res, JPEGCodec::FORMAT_RGB, width, height,
                    width * 3, 100, &output);
  ofstream outfile("test.jpg", std::ofstream::binary);
  outfile.write((char *)&output[0], output.size());
  return 0;
}
