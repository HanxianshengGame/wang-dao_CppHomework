// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#include "MutexLock.h"
#include <cstdio>
namespace threadpool {

MutexLock::MutexLock() {
  if(pthread_mutex_init(&mutex_, nullptr)) {
    perror("pthread_mutex_init");
  }

}
MutexLock::~MutexLock() {
  if(pthread_mutex_destroy(&mutex_)) {
    perror("pthread_mutex_destory");
  }
}
void MutexLock::lock() {
  if(pthread_mutex_lock(&mutex_)) {
    perror("pthread_mutex_lock");
  }
}
void MutexLock::unlock() {
  if(pthread_mutex_unlock(&mutex_)) {
    perror("pthread_mutex_unlock");
  }
}
}
