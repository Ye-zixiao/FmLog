//
// Created by Ye-zixiao on 2021/7/28.
//

#include "include/Log.h"
#include <memory>
#include <cassert>
#include "util/BaseLogger.h"
#include "util/StdLogger.h"
#include "util/AsyncLogger.h"

namespace fm::log {

std::unique_ptr<BaseLogger> logger;
std::atomic<BaseLogger *> atomic_logger{};

void initialize(StdLoggerTag) {
  logger = std::make_unique<StdLogger>();
  atomic_logger.store(logger.get(), std::memory_order_release);
}

void initialize(AsyncLoggerTag,
                const std::string &log_directory,
                const std::string &log_file_name,
                uint32_t log_file_roll_size_mb) {

}

bool FmLog::operator==(LogLine &log_line) {
  assert(atomic_logger.load(std::memory_order_relaxed));
  atomic_logger.load(std::memory_order_acquire)->add(std::move(log_line));
  return true;
}

} // namespace fm::log