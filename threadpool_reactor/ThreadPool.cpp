// Authors: Handling
// Created by 15870 on 2020/10/26.
// This is 

#include <func.h>
#include "ThreadPool.h"

#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif

using std::unique_ptr;
using std::bind;
using std::to_string;
namespace concurrentserver {

ThreadPool::ThreadPool(size_t thread_num, size_t que_sz)
: thread_num_(thread_num)
, que_sz_(que_sz)
, task_queue_(que_sz_)
, is_exit_(false)
{
#ifdef TEST
  cout << "ThreadPool::ThreadPool(size_t thread_num, size_t que_sz)" << endl;
#endif
  threads_.reserve(thread_num_);
}
ThreadPool::~ThreadPool() {
#ifdef TEST
  cout << "ThreadPool::~ThreadPool()" << endl;
#endif
  if(!is_exit_)
    Stop();
}
void ThreadPool::Start() {
#ifdef TEST
  cout << "void ThreadPool::Start() " << endl;
#endif
  for(size_t idx = 0; idx != thread_num_; ++idx) {
    unique_ptr<Thread> up(new Thread(
    	bind(&ThreadPool::ThreadFunc, this),
    	"thread" + to_string(idx+1)
    	));
    threads_.push_back(std::move(up));
  }

  for(auto &thread : threads_)
    thread->Start();
}
void ThreadPool::Stop() {
#ifdef TEST
  cout << "void ThreadPool::Stop()" << endl;
#endif
  if(!is_exit_) {
    while (!task_queue_.Empty())
      sleep(1);

    is_exit_ = true;
    task_queue_.WakeUp(); //要退出了，讲thread全部唤醒

    for(auto &thread : threads_)
      thread->Join();
  }
}
void ThreadPool::AddTask(Task &&task) {
#ifdef TEST
  cout << "void ThreadPool::AddTask(Task &&task)" << endl;
#endif
  task_queue_.Push(task);
}
Task ThreadPool::GetTask() {
#ifdef TEST
  cout << "Task ThreadPool::GetTask() " << endl;
#endif
  return task_queue_.Pop();
}

void ThreadPool::ThreadFunc() {
#ifdef TEST
  cout << "void ThreadPool::ThreadFunc()" << endl;
#endif
  while (!is_exit_) {
    Task task = GetTask();
    if(task)
      task();
  }
}
}
