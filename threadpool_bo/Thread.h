// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_THREAD_H_
#define CPPHOMEWORK_THREADPOOL_THREAD_H_
#include "Nocopyable.h"
#include <pthread.h>
#include <functional>
using std::function;
namespace threadpool {

namespace current_thread {
extern __thread const char *name; //线程名字
}

class Thread: Nocopyable {
  using ThreadCallBack = function<void()>;

 public:
  explicit Thread(const std::string &name, ThreadCallBack &&call_back);
  virtual ~Thread();

  void start();
  void join();

  pthread_t thread_id() const { return thread_id_; }
  std::string thread_name() const { return thread_name_; }

 private:
  static void *ThreadFunc(void *arg);

 private:
  pthread_t thread_id_;
  bool      is_running_;
  ThreadCallBack call_back_; // 回调函数
  std::string thread_name_;
};
}

#endif //CPPHOMEWORK_THREADPOOL_THREAD_H_
