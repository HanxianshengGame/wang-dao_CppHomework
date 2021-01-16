// Authors: Handling
// Created by 15870 on 2020/10/26.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_THREAD_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_THREAD_H_
#include <pthread.h>
#include <string>
#include <functional>
#include "Noncopyable.h"
namespace concurrentserver {
namespace current_thread {
extern __thread const char *name;  //正在执行的线程的名字
}
class Thread : Noncopyable {
 public:
  using ThreadCallback = std::function<void()>;
  Thread(ThreadCallback &&cb, std::string name);
  ~Thread();

  void Start();
  void Join();

  pthread_t thread_id() const { return thread_id_; }

 private:
  static void *ThreadFunc(void *arg);

 private:
  pthread_t thread_id_;
  bool is_running_;
  ThreadCallback  cb_; //回调函数
  std::string  name_;

};
}

#endif //CPPHOMEWORK_THREADPOOL_REACTOR_THREAD_H_
