// Copyright 2012 The Cryptogram Authors.

#include <deque>
#include <iostream>

#include "glog/logging.h"
#include "queue.h"

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);

  LOG(ERROR) << "hi";
  Queue queue(10);

  int one = 1;
  int two = 2;
  int three = 3;
  queue.put(&one, true, 0);
  queue.put(&two, true, 0);
  queue.put(&three, true, 0);
  
  std::string pempty = queue.empty() ? "empty" : "not empty";
  LOG(ERROR) << "Hello: " << pempty;

  while (!queue.empty()) {
    void *v = queue.get(true, 0);
    int *i = static_cast<int *>(v);
    std::cout << i << std::endl;
  }
  
  return 0;
}
