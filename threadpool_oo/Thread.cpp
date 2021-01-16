// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#include "Thread.h"
#include <cstdio>
namespace threadpool {

Thread::Thread()
: thread_id_(0), is_running_(false) {

}
Thread::~Thread() {
  if(is_running_)
    pthread_detach(thread_id_);
}
void Thread::start() {
  if(pthread_create(&thread_id_, nullptr, ThreadFunc, this)) {
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
  Thread *p = static_cast<Thread*>(arg);
  if(p) {
    p->run();
  }
  return nullptr;
}
}
