// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_THREAD_H_
#define CPPHOMEWORK_THREADPOOL_THREAD_H_
#include "Nocopyable.h"
#include <pthread.h>
namespace threadpool {
class Thread: Nocopyable {

 public:
  Thread();
  virtual ~Thread();

  void start();
  void join();

 private:
  virtual void run() = 0;
  static void *ThreadFunc(void *arg);

 private:
  pthread_t thread_id_;
  bool      is_running_;
};
}

#endif //CPPHOMEWORK_THREADPOOL_THREAD_H_
