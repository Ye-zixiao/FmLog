//
// Created by Ye-zixiao on 2021/7/29.
//

#include <atomic>
#include <thread>
#include <string>
#include <iostream>
#include "util/LogBufferQueue.h"
using namespace std;
using namespace fm::log;

std::atomic<bool> g_flag(false);

int main() {
  LogBufferQueue log_buffer_queue{};

  thread t1([&log_buffer_queue] {
    LogLine log_line{};
    int count = 0;
    while (!g_flag.load(std::memory_order_acquire));
    for (int i = 0; i < 210000; ++i) {
      if (log_buffer_queue.pop(log_line)) {
        log_line.stringify(cout);
        if (++count == 10000) {
          fprintf(stderr, "t1 thread pop a log line\n");
          count = 0;
        }
      }
    }
  });
  g_flag.store(true, std::memory_order_release);
  thread t2([&log_buffer_queue] {
    for (int i = 0; i < 100000; ++i) {
      LogLine log_line(fm::log::LogLevel::kERROR, 2, __FILE__, __LINE__);
      log_line << "hello world, " << std::string_view("show me the code");
      log_buffer_queue.push(std::move(log_line));
    }
    fprintf(stderr, "t2 thread push done\n");
  });
  for (int i = 0; i < 100000; ++i) {
    LogLine log_line(fm::log::LogLevel::kDEBUG, 1, __FILE__, __LINE__);
    log_line << "pi: " << 3.1425926 << ", root(3): " << 1.7320508075688;
    log_buffer_queue.push(std::move(log_line));
  }

  fprintf(stderr, "main thread push done\n");

  t1.join();
  t2.join();

  int new_time, reuse_time, backup_push_time, backup_pop_time;
  getAllocation(new_time, reuse_time, backup_push_time, backup_pop_time);
  cerr << "new time: " << new_time << ", reuse time: " << reuse_time
       << ", backup push time: " << backup_push_time << ", backup pop time: "
       << backup_pop_time << endl;

  return 0;
}

