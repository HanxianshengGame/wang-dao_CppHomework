// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is

#include "ThreadPool.h"
#include "Thread.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <unistd.h>


using std::cout;
using std::endl;
using std::unique_ptr;
using threadpool::Task;
using threadpool::ThreadPool;
class MyTask {
 public:
  void process() {
    ::srand(::clock());
    int number = ::rand() % 100;
    cout << threadpool::current_thread::name
         << ": number" << number << endl;

    ::sleep(2);
  }
};


int main() {
  cout << "main thread" << pthread_self() << endl;

  ThreadPool thread_pool(4, 10);
  thread_pool.start();

  int cnt = 20;

  while(cnt-- > 0)
    thread_pool.add_task(std::bind(&MyTask::process, MyTask()));
  thread_pool.stop();

}

