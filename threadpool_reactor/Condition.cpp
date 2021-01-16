// Authors: Handling
// Created by 15870 on 2020/10/26.
// This is 条件变量

#include "Condition.h"
#include "MutexLock.h"
#include <cstdio>
#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif
namespace concurrentserver {

Condition::Condition(MutexLock &mutex)
: mutex_(mutex) {
#ifdef TEST
  cout << "Condition::Condition(MutexLock &mutex)" << endl;
#endif
  if(pthread_cond_init(&cond_, nullptr))
    perror("pthread_cond_init");
}
Condition::~Condition() {
#ifdef TEST
  cout << "Condition::~Condition()" << endl;
#endif
  if(pthread_cond_destroy(&cond_))
    perror("pthread_cond_destory");
}
void Condition::Wait() {
#ifdef TEST
  cout << "void Condition::Wait() " << endl;
#endif
  if(pthread_cond_wait(&cond_, mutex_.mutex_ptr()))
    perror("pthread_cond_signal");
}
void Condition::Notify() {
#ifdef TEST
  cout << "void Condition::Notify()" << endl;
#endif
  if(pthread_cond_signal(&cond_))
    perror("pthread_cond_signal");
}
void Condition::NotifyAll() {
#ifdef TEST
  cout << "void Condition::NotifyAll()" << endl;
#endif
  if(pthread_cond_broadcast(&cond_))
    perror("pthread_cond_broadcast");
}
}