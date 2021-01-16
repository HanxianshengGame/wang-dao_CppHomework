// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#include "Thread.h"
#include <cstdio>
namespace threadpool {

namespace current_thread {
__thread const char *name = "thread";
}


using ThreadCallBack = function<void()>;

struct ThreadData {
  std::string name_;
  ThreadCallBack  cb_;

  ThreadData(const std::string &name, ThreadCallBack &&cb)
  :name_(name)
  ,cb_(std::move(cb))
  { }

  //执行注册的回调函数前赋予名字
  void RunInThread() {
    current_thread::name = (name_ == std::string()) ?
    	                    "thread" : name_.c_str();
    if(cb_)
      cb_();
  }
};

Thread::Thread(const std::string &name, ThreadCallBack &&call_back)
: thread_id_(0)
, is_running_(false)
, call_back_(std::move(call_back))
, thread_name_(name)
{

}
Thread::~Thread() {
  if(is_running_)
    pthread_detach(thread_id_);
}
void Thread::start() {
  ThreadData *data = new ThreadData(thread_name_, std::move(call_back_));
  if(pthread_create(&thread_id_, nullptr, ThreadFunc, data)) {
    perror("thread_create");
	return;
  }

}
void Thread::join() {
  if(is_running_) {
    pthread_join(thread_id_, nullptr);
  }
}
void *Thread::ThreadFunc(void *arg) {

  ThreadData *p = static_cast<ThreadData*>(arg);
  if(p) {
    p->RunInThread();
  }
  return nullptr;
}
}
