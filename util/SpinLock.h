//
// Created by Ye-zixiao on 2021/7/28.
//

#ifndef FMLOG_UTIL_SPINLOCK_H_
#define FMLOG_UTIL_SPINLOCK_H_

#include <atomic>

namespace fm::log {

class SpinLock {
 public:
  explicit SpinLock(std::atomic_flag &flag)
      : flag_(flag) {
    while (flag_.test_and_set(std::memory_order_acquire)) {}
  }

  ~SpinLock() {
    flag_.clear(std::memory_order_release);
  }

 private:
  std::atomic_flag &flag_;
};

} // namespace fm::log

#endif //FMLOG_UTIL_SPINLOCK_H_
