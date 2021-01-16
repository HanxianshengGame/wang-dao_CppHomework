// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_CONDITION_H_
#define CPPHOMEWORK_THREADPOOL_CONDITION_H_

#include "Nocopyable.h"
#include <pthread.h>

namespace threadpool {
class MutexLock;
class Condition: Nocopyable {
 public:
  explicit Condition(MutexLock &mutex);
  ~Condition();

  void wait();
  void notify();
  void notify_all();
 private:
  pthread_cond_t cond_;
  MutexLock &mutex_;

};
}

#endif //CPPHOMEWORK_THREADPOOL_CONDITION_H_
