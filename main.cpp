#include <iostream>
#include "include/Log.h"
using namespace std;

int main() {
  fm::log::initialize(fm::log::StdLoggerTag{});
  for (int i = 0; i < 1000; ++i)
    LOG_INFO << "test log info";
  return 0;
}