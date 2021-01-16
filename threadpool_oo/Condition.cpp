// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#include "Condition.h"
#include <cstdio>
#include "MutexLock.h"
threadpool::Condition::Condition(threadpool::MutexLock &mutex): mutex_(mutex) {
  if(pthread_cond_init(&cond_, nullptr)) {
    perror("pthread_cond_init");
  }
}
threadpool::Condition::~Condition() {
  if(pthread_cond_destroy(&cond_)) {
    perror("pthread_cond_destroy");
  }
}
void threadpool::Condition::wait() {
  if(pthread_cond_wait(&cond_, mutex_.GetMutexLockPtr())) {
    perror("pthread_cond_wait");
  }
}
void threadpool::Condition::notify() {
  if(pthread_cond_signal(&cond_)) {
    perror("pthread_cond_signal");
  }
}
void threadpool::Condition::notify_all() {
  if(pthread_cond_broadcast(&cond_)) {
    perror("pthread_cond_broadcast");
  }
}
