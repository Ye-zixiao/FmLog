//
// Created by Ye-zixiao on 2021/7/28.
//

#ifndef FMLOG_INCLUDE_LOG_H_
#define FMLOG_INCLUDE_LOG_H_

#include <string>
#include "util/LogLine.h"
#include "util/TimeStamp.h"
#include "util/SystemClock.h"

namespace fm::log {

struct StdLoggerTag {};
struct AsyncLoggerTag {};

void initialize(StdLoggerTag);
void initialize(AsyncLoggerTag,
                const std::string &log_directory,
                const std::string &log_file_name,
                uint32_t log_file_roll_size_mb);

struct FmLog {
  bool operator==(LogLine &log_line);
};

} // namespace fm::log

#define LOG(LEVEL) fm::log::FmLog() == fm::log::LogLine(LEVEL, errno, __FILE__, __LINE__)
#define LOG_FATAL LOG(fm::log::LogLevel::kFATAL)
#define LOG_DEBUG LOG(fm::log::LogLevel::kDEBUG)
#define LOG_ERROR LOG(fm::log::LogLevel::kERROR)
#define LOG_WARN LOG(fm::log::LogLevel::kWARN)
#define LOG_INFO LOG(fm::log::LogLevel::kINFO)

#endif //FMLOG_INCLUDE_LOG_H_
