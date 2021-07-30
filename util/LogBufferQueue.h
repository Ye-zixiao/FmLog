//
// Created by Ye-zixiao on 2021/7/27.
//

#ifndef FMLOG_UTIL_LOGBUFFERQUEUE_H_
#define FMLOG_UTIL_LOGBUFFERQUEUE_H_

#include <atomic>
#include <memory>
#include <queue>
#include "util/LogLine.h"

namespace fm::log {

void getAllocation(int &new_time, int &reuse_time,
                   int &backup_push_time, int &backup_pop_time);

class LogBuffer {
 public:
  struct Item {
    char padding[256 - sizeof(LogLine)]{};
    LogLine log_line;
    Item(LogLine &&ll) noexcept: log_line(std::move(ll)) {}
    ~Item() = default;
  };

//   简单测试了下每次分配1M（4096*256）的空间性能更好
  static constexpr size_t kSize = 4096;

  LogBuffer();
  ~LogBuffer();

  bool push(LogLine &&log_line, size_t write_index);
  bool pop(LogLine &log_line, size_t read_index);

  LogBuffer(const LogBuffer &) = delete;
  LogBuffer &operator=(const LogBuffer &) = delete;

 private:
  // 最后一个元素用来存放日志缓冲块中日志行的数量，其他用来表示日志行的有效状态
  std::atomic<size_t> write_states_[kSize + 1];
  Item *items_;
};

template<size_t SIZE>
class RingQueue {
 public:
  // 将类模板的成员函数定义在唯一include它的源文件中这样的手段是允许的
  RingQueue();

  bool push(std::unique_ptr<LogBuffer> &&log_buffer);
  bool pop(std::unique_ptr<LogBuffer> &log_buffer);

 private:
  std::unique_ptr<LogBuffer> log_buffers_[SIZE + 1];
  size_t write_index_, read_index_;
  std::atomic_flag flag_;
};

class LogBufferQueue {
 public:
  LogBufferQueue();

  LogBufferQueue(const LogBufferQueue &) = delete;
  LogBufferQueue &operator=(const LogBufferQueue &) = delete;

  void push(LogLine &&log_line);
  bool pop(LogLine &log_line);

 private:
  void setupNextWriteLogBuffer();
  LogBuffer *getNextReadLogBuffer();

 private:
  std::queue<std::unique_ptr<LogBuffer>> log_buffers_;
  std::atomic<LogBuffer *> current_write_buffer_;
  LogBuffer *current_read_buffer_;
  std::atomic<size_t> write_index_;
  size_t read_index_;
  std::atomic_flag flag_;
  RingQueue<5> backup_log_buffers_;
};

} // namespace fm::log

#endif //FMLOG_UTIL_LOGBUFFERQUEUE_H_
