//
// Created by Ye-zixiao on 2021/7/27.
//

#ifndef FMLOG_UTIL_STDLOGGER_H_
#define FMLOG_UTIL_STDLOGGER_H_

#include <atomic>
#include "util/BaseLogger.h"

namespace fm::log {

class StdLogger : public BaseLogger {
 public:
  // StdLogger的主要工作就是向stdout输出日志行

  ~StdLogger() override = default;
  void add(LogLine &&log_line) override;

 private:
  std::atomic_flag flag_{};
};

} // namespace fm::log

#endif //FMLOG_UTIL_STDLOGGER_H_
