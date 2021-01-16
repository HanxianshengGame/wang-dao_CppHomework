// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_WORKERTHREAD_H_
#define CPPHOMEWORK_THREADPOOL_WORKERTHREAD_H_
#include "Thread.h"
namespace threadpool {

class ThreadPool;

class WorkerThread: public Thread {
 public:
  explicit WorkerThread(ThreadPool &thread_pool);
 private:
  void run() override;
 private:
  ThreadPool &thread_pool_;
};
}

#endif //CPPHOMEWORK_THREADPOOL_WORKERTHREAD_H_
