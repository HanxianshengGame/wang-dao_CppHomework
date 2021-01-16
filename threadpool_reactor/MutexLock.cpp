// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 

#include "MutexLock.h"
#include <cstdio>
#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif
namespace concurrentserver {

MutexLock::MutexLock() {
#ifdef TEST
  cout << "MutexLock::MutexLock()  " << endl;
#endif
  if(pthread_mutex_init(&mutex_, nullptr))
    perror("pthread_mutex_init");
}
MutexLock::~MutexLock() {
#ifdef TEST
  cout << "MutexLock::~MutexLock()  " << endl;
#endif
  if(pthread_mutex_destroy(&mutex_))
    perror("pthread_mutex_destory");
}
void MutexLock::Lock() {
#ifdef TEST
  cout << "void MutexLock::Lock() " << endl;
#endif
  if(pthread_mutex_lock(&mutex_))
    perror("pthread_mutex_lock");
}
void MutexLock::Unlock() {
#ifdef TEST
  cout << "void MutexLock::Unlock() " << endl;
#endif
  if(pthread_mutex_unlock(&mutex_))
    perror("pthread_mutex_unlock");
}
}