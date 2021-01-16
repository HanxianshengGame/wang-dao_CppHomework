// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_THREADPOOL_H_
#define CPPHOMEWORK_THREADPOOL_THREADPOOL_H_
#include "TaskQueue.h"
#include "Task.h"
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;
namespace threadpool {
class Thread;
class ThreadPool {
  friend class WorkerThread;
 public:
  ThreadPool(size_t thread_num, size_t que_size);
  ~ThreadPool();

  void start();
  void stop();
  void add_task(Task *);

 private:
  Task *get_task();
  void thread_func();

 private:
  size_t thread_num_;
  size_t que_size_;
  vector<unique_ptr<Thread>> threads_;
  TaskQueue task_queue_;
  bool is_exit_;


};
}

#endif //CPPHOMEWORK_THREADPOOL_THREADPOOL_H_
