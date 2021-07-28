//
// Created by Ye-zixiao on 2021/7/28.
//

#ifndef FMLOG_UTIL_BASELOGGER_H_
#define FMLOG_UTIL_BASELOGGER_H_

namespace fm::log {

class LogLine;

class BaseLogger {
 public:
  virtual ~BaseLogger() = default;
  virtual void add(LogLine &&log_line) = 0;
};

} // namespace fm::log

#endif //FMLOG_UTIL_BASELOGGER_H_
