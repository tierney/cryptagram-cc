// Copyright 2012. The Cryptogram Authors. BSD License.
// Author: tierney@cs.nyu.edu (Matt Tierney)

#include <cstdlib>
#include <string>

#include "aesthete.h"
#include "aesthete_thread.h"
#include "glog/logging.h"
#include "google/gflags.h"
#include "queue.h"
#include "reentrant_rand.h"
#include "types.h"

DEFINE_int32(gen_threads, 1, "Number of generator threads.");
DEFINE_int32(run_threads, 1, "Number of runner threads.");
DEFINE_int64(num_matrices, 1000000, "Number of matrices to generate "
             "(technically, num_matrices divided by gen_threads).");
DEFINE_int32(queue_size, 10000, "Maximum number of chunks to hold in queue.");
DEFINE_string(input_file, "matrices.txt", "Input file for matrices.");

DECLARE_int64(chunk_size);

const int kBytesPerMatrix = 6;

namespace {

void usage() {
  std::cout << "In memory experiment for the Cryptogram project." << std::endl;
#ifdef HAVE_LIBTCMALLOC
  std::cout << "--> Using libtcmalloc." << std::endl;
#endif

  if (FLAGS_queue_size > 0) {
    std::cout << "--> Queue size: " << FLAGS_queue_size << std::endl;
  }
}

} // namespace

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, false);

  usage();

  Queue queue(FLAGS_queue_size);

  vector<cryptogram::aesthete::Generator*> generators;
  for (int i = 0; i < FLAGS_gen_threads; i++) {
    generators.push_back(
        new cryptogram::aesthete::Generator(
            0,
            FLAGS_num_matrices / FLAGS_gen_threads,
            FLAGS_chunk_size,
            &queue));

  }
  for (int i = 0; i < FLAGS_gen_threads; i++) {
    generators[i]->Start();
  }

  vector<cryptogram::AestheteRunner*> runners;
  for (int i = 0; i < FLAGS_run_threads; i++) {
    runners.push_back(new cryptogram::AestheteRunner(
        i, FLAGS_num_matrices, &queue));
  }
  for (int i = 0; i < FLAGS_run_threads; i++) {
    runners[i]->Start();
  }

  queue.join();

  for (int i = 0; i < FLAGS_gen_threads; i++) {
    generators[i]->Join();
  }

  for (int i = 0; i < FLAGS_run_threads; i++) {
    runners[i]->Done();
  }

  std::cout << "Finished generating matrices for queue." << std::endl;
  std::cout << "Waiting for the runners to finish." << std::endl;
  for (int i = 0; i < FLAGS_run_threads; i++) {
    runners[i]->Join();
  }

  for (int i = 0; i < FLAGS_gen_threads; i++) {
    delete generators[i];
  }
  for (int i = 0; i < FLAGS_run_threads; i++) {
    delete runners[i];
  }
  return 0;
}
