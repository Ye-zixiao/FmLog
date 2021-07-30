//
// Created by Ye-zixiao on 2021/7/27.
//

#ifndef FMLOG_UTIL_ASYNCLOGGER_H_
#define FMLOG_UTIL_ASYNCLOGGER_H_

#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include "util/BaseLogger.h"

namespace fm::log {

class LogLine;
class LogFile;
class LogBufferQueue;

class AsyncLogger : public BaseLogger {
 public:
  AsyncLogger(const std::string &log_directory,
              const std::string &log_file_name,
              uint32_t roll_file_size_max);

  ~AsyncLogger();

  void add(LogLine &&log_line) override;

 private:
  void popThread();

 private:
  enum class STATE { kINIT, kREADY, kSHUTDOWN };

  std::atomic<STATE> state_;
  std::unique_ptr<LogBufferQueue> buffer_queue_;
  std::unique_ptr<LogFile> log_file_;
  std::thread background_thread_;
};

} // namespace fm::log

#endif //FMLOG_UTIL_ASYNCLOGGER_H_
