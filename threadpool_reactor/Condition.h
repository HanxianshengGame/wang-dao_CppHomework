// Authors: Handling
// Created by 15870 on 2020/10/26.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_CONDITION_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_CONDITION_H_

#include "Noncopyable.h"
#include <pthread.h>

namespace concurrentserver {

class MutexLock;

class Condition : Noncopyable {
 public:
  explicit Condition(MutexLock &mutex);
  ~Condition();

  void Wait();
  void Notify();
  void NotifyAll();

 private:
  pthread_cond_t cond_{};
  MutexLock     &mutex_;
};
}

#endif //CPPHOMEWORK_THREADPOOL_REACTOR_CONDITION_H_
