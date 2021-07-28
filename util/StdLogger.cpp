//
// Created by Ye-zixiao on 2021/7/28.
//

#include "util/StdLogger.h"
#include <iostream>
#include "util/LogLine.h"
#include "util/SpinLock.h"

namespace fm::log {

void StdLogger::add(LogLine &&log_line) {
  SpinLock spin_lock(this->flag_);
  log_line.stringify(std::cout);
}

} // namespace fm::log