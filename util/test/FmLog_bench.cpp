//
// Created by Ye-zixiao on 2021/7/30.
//

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <libgen.h>
#include "fmlog/Log.h"
using namespace std::chrono_literals;

void bench(bool long_log) {
  int cnt = 0;
  const int kBatch = 1000;
  std::string empty(" ");
  std::string long_str(3000, 'X');
  long_str += " ";

  for (int i = 0; i < 30; ++i) {
    auto start_time = fm::time::SystemClock::now();
    for (int j = 0; j < kBatch; ++j) {
      LOG_INFO << "Hello 0123456789" << " abcdefghjklmnopqrstuvwxyz"
               << (long_log ? long_str : empty) << cnt++;
    }

    auto end_time = fm::time::SystemClock::now();
    // 平均输出每一条日志需要多少时间（单位微秒us）
    printf("%f\n", static_cast<double>((end_time - start_time).count()) / kBatch);
    std::this_thread::sleep_for(500ms);
  }
}

int main(int argc, char *argv[]) {
  printf("pid = %d\n", ::getpid());

  constexpr uint32_t mb = 1024 * 1024;
  fm::log::initialize(fm::log::AsyncLoggerTag{}, "./",
                      ::basename(argv[0]), 100 * mb);
  bool long_log = argc > 1;
  bench(long_log);
  return 0;
}

/**
* 试验平台：12G ddr3-1600 内存，i7-4790 CPU，东芝Toshiba-TR200 SSD Win10-wsl-Ubuntu
* 实验结果：
/mnt/e/Desktop/FmLog/build/bin$ ./FmLog_bench
pid = 26113
0.153000
0.158000
0.156000
0.162000
0.191000
0.735000
0.131000
0.117000
0.141000
0.117000
0.130000
0.119000
0.139000
0.123000
0.117000
0.124000
0.136000
0.172000
0.117000
0.116000
0.122000
0.126000
0.167000
0.161000
0.199000
0.169000
0.188000
0.173000
0.168000
0.160000
 也就是说平均每一条日志输出所需的时间为0.2微秒之内

 * 作为对比，给出muduo中实现的日志库成绩：
~/CodeFxcker/build/release-cpp11/bin$ ./asynclogging_test
pid = 23779
0.301000
0.292000
0.256000
0.320000
0.255000
0.254000
0.255000
0.248000
0.246000
0.268000
0.246000
0.260000
0.276000
0.293000
0.259000
0.248000
0.258000
0.247000
0.399000
0.245000
0.287000
0.245000
0.278000
0.245000
0.277000
0.248000
0.271000
0.257000
0.389000
0.247000
*/