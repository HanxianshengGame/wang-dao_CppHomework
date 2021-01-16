// Authors: Handling
// Created by 15870 on 2020/10/26.
// This is 

#include "Thread.h"
#include <cstdio>

#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif

namespace concurrentserver {

namespace current_thread {
__thread const char *name = "thread";  //线程局部存储，每个线程都有自己对其的一份拷贝
}

using ThreadCallback = Thread::ThreadCallback;

struct ThreadData {
  std::string name_;
  ThreadCallback cb_;
  ThreadData(std::string name, ThreadCallback cb)
  : name_(std::move(name))
  , cb_(std::move(cb))
  {
#ifdef TEST
	cout << "ThreadData(std::string name, ThreadCallback cb)" << endl;
#endif

  }

  void RunInThread() const {
#ifdef TEST
	cout << "void RunInThread() const" << endl;
#endif
    //在回调函数执行之前进行对 线程名称 的赋值
    current_thread::name = (name_.empty()) ? "thread" : name_.c_str();
    if(cb_)
      cb_();

    //...
  }
};

Thread::Thread(Thread::ThreadCallback &&cb, std::string name = std::string())
: thread_id_(0)
, is_running_(false)
, cb_(std::move(cb))
, name_(std::move(name)) {

#ifdef TEST
  cout << "Thread::Thread(Thread::ThreadCallback &&cb, std::string name = std::string())" << endl;
#endif
}
Thread::~Thread() {
#ifdef TEST
  cout << "Thread::~Thread()" << endl;
#endif
  if(is_running_)
    pthread_detach(thread_id_);
}
void Thread::Start() {
#ifdef TEST
  cout << "void Thread::Start()" << endl;
#endif
  auto *data = new ThreadData(name_, cb_);
  if(pthread_create(&thread_id_, nullptr, ThreadFunc, data)) {
    perror("pthread_create");
	return;
  }
  is_running_ = true;
}
void Thread::Join() {
#ifdef TEST
  cout << "void Thread::Join()" << endl;
#endif
  if(is_running_) {
    pthread_join(thread_id_, nullptr);
    is_running_ = false;
  }
}

void *Thread::ThreadFunc(void *arg) {
#ifdef TEST
  cout << "void *Thread::ThreadFunc(void *arg)" << endl;
#endif
  auto *p = static_cast<ThreadData*>(arg);
  if(p)
    p->RunInThread();
  delete p;
  return nullptr;
}
}