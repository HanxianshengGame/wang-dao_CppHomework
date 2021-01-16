// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_MUTEXLOCK_H_
#define CPPHOMEWORK_THREADPOOL_MUTEXLOCK_H_
#include "Nocopyable.h"
#include <pthread.h>
namespace threadpool {
class MutexLock: Nocopyable {
 public:
  MutexLock();
  ~MutexLock();

  void lock();
  void unlock();

  pthread_mutex_t* GetMutexLockPtr() { return &mutex_; }
 private:
  pthread_mutex_t mutex_;
};

class MutexLockGuard {
 public:
  explicit MutexLockGuard(MutexLock &mutex)
  : mutex_(mutex) {
    mutex_.lock();
  }

  ~MutexLockGuard() {
    mutex_.unlock();
  }

 private:
  MutexLock &mutex_;
};
}

#endif //CPPHOMEWORK_THREADPOOL_MUTEXLOCK_H_
