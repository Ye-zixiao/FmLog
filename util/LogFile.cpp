//
// Created by Ye-zixiao on 2021/7/27.
//

#include "util/LogFile.h"
#include "util/LogLine.h"

namespace fm::log {

void LogFile::write(LogLine &log_line) {
  auto curr = roll_file_->tellp();
  log_line.stringify(*roll_file_);
  writen_bytes_ += roll_file_->tellp() - curr;
  if (writen_bytes_ > roll_file_size_max_)
    rollFile();
}

} // namespace fm::log