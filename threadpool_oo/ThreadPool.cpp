// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#include "ThreadPool.h"
#include "WorkerThread.h"
#include <func.h>
namespace threadpool {
ThreadPool::ThreadPool(size_t thread_num, size_t que_size)
: thread_num_(thread_num),
  que_size_(que_size),
  task_queue_(que_size),
  is_exit_(false) {
  threads_.reserve(thread_num);
}
ThreadPool::~ThreadPool() {
  if(!is_exit_) {
    stop();
  }
}
void ThreadPool::start() {
  for(size_t index = 0; index != thread_num_; ++index) {
    unique_ptr<Thread> up(new WorkerThread(*this));
    threads_.push_back(std::move(up));
  }
  for(auto &pthread : threads_)
    pthread->start();
}
void ThreadPool::stop() {
  if(!is_exit_) {
    while(!task_queue_.empty()) {
      ::sleep(1);
    }
    is_exit_ = true;
    task_queue_.exit();  //让任务队列也退出
    for(auto &pthread : threads_)
      pthread->join();

  }
}
void ThreadPool::add_task(threadpool::Task *task) {
  task_queue_.push(task);
}
Task *ThreadPool::get_task() {
  return task_queue_.pop();
}
void ThreadPool::thread_func() {
  while(!is_exit_) {
    Task *ptask = get_task();
    if(ptask)
      ptask->process();
  }
}
}