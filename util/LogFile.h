//
// Created by Ye-zixiao on 2021/7/27.
//

#ifndef FMLOG_UTIL_LOGFILE_H_
#define FMLOG_UTIL_LOGFILE_H_

#include <string>
#include <memory>
#include <fstream>
#include <unistd.h>

namespace fm::log {

class LogLine;

class LogFile {
 public:
  LogFile(const std::string &log_directory,
          const std::string &log_file_name,
          uint32_t roll_file_size)
      : log_file_name_(log_directory + log_file_name),
        roll_file_size_max_(roll_file_size),
        roll_file_(),
        writen_bytes_(0),
        file_num_(0) {
    rollFile();
  }

  void write(LogLine &log_line);

 private:
  void rollFile() {
    if (roll_file_) {
      roll_file_->flush();
      roll_file_->close();
    }

    writen_bytes_ = 0;
    roll_file_ = std::make_unique<std::ofstream>();
    std::string next_roll_file_name = log_file_name_;
    next_roll_file_name.append(".");
    next_roll_file_name.append(std::to_string(file_num_++));
    next_roll_file_name.append(".log");
    roll_file_->open(next_roll_file_name, std::ofstream::out | std::ofstream::trunc);
  }

 private:
  std::string log_file_name_;
  const uint32_t roll_file_size_max_;
  std::unique_ptr<std::ofstream> roll_file_;
  std::streamoff writen_bytes_;
  uint32_t file_num_;
};

} // namespace fm::log

#endif //FMLOG_UTIL_LOGFILE_H_
