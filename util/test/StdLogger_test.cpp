//
// Created by Ye-zixiao on 2021/7/28.
//

#include <thread>
#include "include/Log.h"
using namespace std;

int main() {
  fm::log::initialize(fm::log::StdLoggerTag{});

  thread t([] {
    char buf[32] = "joker is not joke";

    for (int i = 0; i < 1000; ++i) {
      LOG_INFO << "hello world" << std::string_view(". talk is cheap")
               << std::string(", show me the code. ") << &buf[6] << 32
               << 123.432 << -424 << INT32_MAX << -.32535;
    }
  });

  for (int i = 0; i < 1000; ++i) {
    errno = 1;
    LOG_ERROR << std::string("fjksdlsdlsdlsdlsdlsdlsdlsdlsdlsdlsdlsdl"
                             "dfjskjfas;kldddddkldkldkldkldkldkldklddfsd"
                             "jfsdklfjkls;jajjjajajajajajajajajajajajajf"
                             "fjklds;s;s;s;s;s;s;s;s;s;s;s;s;s;s;s;s;s;s"
                             "string end------");
  }

  t.join();

  return 0;
}