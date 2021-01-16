// Authors: Handling
// Created by 15870 on 2020/10/14.
// This is MultiThread technology

#include <pthread.h>
#include <func.h>
#include <bits/stdc++.h>
using namespace std;
#define CHECK(exp)\
    if(exp == -1) \
    { \
       fprintf(stderr,"file:%s,line:%d Exp:[" #exp "] not return 0\n",__FILE__,__LINE__);abort();\
    }

// 设置不可拷贝的基类
class noncopyable {
 protected:
  noncopyable() = default;
  ~noncopyable() = default;
 public:
  noncopyable(const noncopyable &rhs) = delete;
  noncopyable &operator=(const noncopyable &rhs) = delete;
};



namespace multithread {
//互斥锁
class MyMutex : public noncopyable {
 public:
  MyMutex();
  void lock();
  void unlock();
  pthread_mutex_t *GetMutexPtr() { return &mutex_; }
  ~MyMutex();
 private:
  pthread_mutex_t mutex_;
};
MyMutex::MyMutex() : mutex_() {
  pthread_mutex_init(&mutex_, nullptr);
}
void MyMutex::lock() {
  CHECK(pthread_mutex_lock(&mutex_));
}
void MyMutex::unlock() {
  CHECK(pthread_mutex_unlock(&mutex_));
}
MyMutex::~MyMutex() {
  CHECK(pthread_mutex_destroy(&mutex_));
}

//RAII 管理锁
class UniqueLock : public noncopyable {
 private:
  MyMutex &mutex_;
 public:
  explicit UniqueLock(MyMutex &mutex);
  ~UniqueLock();
};
UniqueLock::UniqueLock(MyMutex &mutex) : mutex_(mutex) {
  mutex_.lock();
}
UniqueLock::~UniqueLock() {
  mutex_.unlock();
}


//条件变量
class MyCondition : noncopyable {
 private:
  MyMutex &mutex_;
  pthread_cond_t cond_;
 public:
  explicit MyCondition(MyMutex &mutex);
  ~MyCondition();
  void wait();
  void notify();
  void notifyall();
};
MyCondition::MyCondition(MyMutex &mutex) : mutex_(mutex), cond_() {
  CHECK(pthread_cond_init(&cond_, nullptr));
}
MyCondition::~MyCondition() {
  CHECK(pthread_cond_destroy(&cond_));
}
void MyCondition::wait() {
  CHECK(pthread_cond_wait(&cond_, mutex_.GetMutexPtr()));
}
void MyCondition::notify() {
  CHECK(pthread_cond_signal(&cond_));
}
void MyCondition::notifyall() {
  CHECK(pthread_cond_broadcast(&cond_));
}


//线程
class MyThread {
 public:
  MyThread();
  virtual ~MyThread();
  void start();
  void join();
  bool joinable() const { return is_running; }
  pthread_t thread_id() const { return thread_id_; }
 private:
  static void* func(void *arg);
  virtual void run() = 0;   //实现任务
 private:
  pthread_t thread_id_;
  bool is_running;
};
MyThread::MyThread(): thread_id_(0), is_running(false) {
}
MyThread::~MyThread() {
  if(joinable()) {
    //使线程ID为threadid的线程处于分离状态，
    // 一旦线程处于分离状态，该线程终止时底 层资源立即被回收；
    // 否则终止子线程的状态会一直保存（占用系统资源）直到主线程调用
    CHECK(pthread_detach(thread_id_));
  }
}
void MyThread::start() {
  CHECK(pthread_create(&thread_id_, nullptr, MyThread::func, (void*)this));
  is_running = true;
}
void MyThread::join() {
  assert(joinable());
  CHECK(pthread_join(thread_id_, nullptr));
  is_running = false;
}
void* MyThread::func(void *arg) {
  auto *my_thread = (MyThread*)arg;
  my_thread->run();
  return nullptr;
}


int count = 0; //测试锁的功能用
int food = 10;

MyMutex mutex;
MyCondition condition(mutex);
MyCondition condition1(mutex);


class TestThread: public MyThread {
  void run() override {
    int i = 10000000;
    while(i--) {
      UniqueLock unique_lck(mutex);
      ++count;
    }
  }
};

class ConsumerThread: public MyThread {
  void run() override {
    while(1) {
      UniqueLock lck(mutex);

      cout << "consumer has get mutex" << endl;
	  if(food == 0)
        condition.wait();
	  sleep(1);
      cout << thread_id() << "eat one" << endl;
      --food;
      if(food == 0)
        condition1.notify();
    }
  }
};

class ProducerThread: public MyThread {
  void run() override {
    while(1) {
	  UniqueLock lck(mutex);

	  cout << "producer has  get mutex" << endl;
	  if(food > 0)
	    condition1.wait();
	  sleep(1);
	  cout << thread_id() << "create one" << endl;
	  ++food;
	  condition.notify();
    }
  }
};

}

int main() {
  using namespace multithread;
//  TestThread test_thread1;
//  TestThread test_thread2;
//  test_thread1.start();
//  test_thread2.start();
//  test_thread1.join();
//  test_thread2.join();
//  cout << multithread::count  << endl;

  ProducerThread producer_thread;
  vector<ConsumerThread> consumer_threads(10);
  producer_thread.start();

  for(int i = 0; i != 10; ++i) {
    consumer_threads[i].start();
  }

  producer_thread.join();
  for(int i = 0; i != 10; ++i) {
    consumer_threads[i].join();
  }
}