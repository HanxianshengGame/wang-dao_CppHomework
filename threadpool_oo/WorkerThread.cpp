// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#include "WorkerThread.h"
#include "ThreadPool.h"
namespace threadpool {

WorkerThread::WorkerThread(ThreadPool &thread_pool)
: thread_pool_(thread_pool) {

}
void WorkerThread::run() {
  thread_pool_.thread_func();
}
}