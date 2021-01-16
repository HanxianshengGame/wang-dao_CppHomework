// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_MUTEXLOCK_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_MUTEXLOCK_H_
#include <pthread.h>
#include "Noncopyable.h"
namespace concurrentserver {

class MutexLock : Noncopyable {
 public:
  MutexLock();
  ~MutexLock();

  void Lock();
  void Unlock();

  pthread_mutex_t *mutex_ptr() { return &mutex_; }
 private:
  pthread_mutex_t mutex_{};
};

class MutexLockGuard {
 public:
  explicit MutexLockGuard(MutexLock &mutex)
  : mutex_(mutex) {

    mutex_.Lock();
  }

  ~MutexLockGuard() {
    mutex_.Unlock();
  }
 private:
  MutexLock &mutex_;
};
}

#endif //CPPHOMEWORK_THREADPOOL_REACTOR_MUTEXLOCK_H_
