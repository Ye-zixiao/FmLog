//
// Created by Ye-zixiao on 2021/7/28.
//

#include "util/StdLogger.h"
#include <iostream>
#include <mutex>
#include "util/LogLine.h"
#include "util/SpinLock.h"

std::mutex g_mutex{};

namespace fm::log {

void StdLogger::add(LogLine &&log_line) {
  SpinLock spin_lock(this->flag_);
//  std::lock_guard<std::mutex> lock_guard(g_mutex);
  log_line.stringify(std::cout);
}

} // namespace fm::log