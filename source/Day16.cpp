// Authors: Handling
// Created by 15870 on 2020/10/6.
// This is  template and args

#include <iostream>
#include <vector>
#include <deque>
#include <exception>
#include <cassert>
#include <log4cpp/SimpleConfigurator.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <cstring>

using namespace log4cpp;
using namespace std;
namespace templateandargs {
template<class T>
class MyQueue {
 private:
  vector<T> data_;
 public:
  void push_back(T &elem);
  void pop_front();
  T &front() const;
  auto size() -> decltype(data_.size()) const;
};
template<class T>
void MyQueue<T>::push_back(T &elem) {
  data_.push_back(elem);
}
template<class T>
void MyQueue<T>::pop_front() {
  if (size())
	data_.erase(data_.begin());
}
template<class T>
T &MyQueue<T>::front() const {
  if (size())
	return *data_.begin();
  assert(true);
}
template<class T>
auto MyQueue<T>::size() -> decltype(data_.size()) const {
  return data_.size();
}

template<class T>
class Singleton {
  friend class AutoRelease;
 public:
  template<typename  ...Args>
  static T *GetInstance(Args ...args) {
	auto_release_; //没有Singleton就没有auto_release_实例，但当用到时即可推导生成其auto_release_;
	return instance_;
  }

 private:
  class AutoRelease {
   public:
	AutoRelease() = default;
	~AutoRelease() {
	  cout << "1" << endl;
	  delete instance_;
	}
  };
  Singleton() { cout << 1 << endl; };
  static T *instance_;
  static AutoRelease auto_release_;
};
template<class T>
T *Singleton<T>::instance_ = new T();

template<class T>
typename Singleton<T>::AutoRelease Singleton<T>::auto_release_;

class Computer {

};
class Point {

};

}

namespace mylog {
class MyLogger {
 public:
  void warn(const char *msg);
  void error(const char *msg);
  void debug(const char *msg);
  void info(const char *msg);
  template<typename ...Args>
  void log(const char *msg, Args ...args) ;
 private:
  MyLogger();
  ~MyLogger();
 public:
  static MyLogger *Instance();
 private:
  static MyLogger *instance;

  PatternLayout *layout1_;
  PatternLayout *layout2_;
  OstreamAppender *ostream_appender_;
  FileAppender *file_appender_;
  Category &category_;
};
MyLogger *MyLogger::instance = new MyLogger();
MyLogger *MyLogger::Instance() {
  return instance;
}

MyLogger::MyLogger() : category_(Category::getRoot().getInstance("main_category")) {
  layout1_ = new PatternLayout();
  layout1_->setConversionPattern("%d %c [%p] %m%n");
  layout2_ = new PatternLayout();
  layout2_->setConversionPattern("%d %c [%p] %m%n");
  ostream_appender_ = new OstreamAppender("cout_appender", &cout);
  ostream_appender_->setLayout(layout1_);
  file_appender_ = new FileAppender("file_appender", "handling.log");
  file_appender_->setLayout(layout2_);
  category_.addAppender(ostream_appender_);
  category_.addAppender(file_appender_);
  category_.setPriority(Priority::DEBUG);
}
void MyLogger::warn(const char *msg) {
  category_.warn("file: %s  line: %d func: %s msg: %s", __FILE__, __LINE__, "warn", msg);
}
void MyLogger::error(const char *msg) {
  category_.error("file: %s  line: %d func: %s msg: %s", __FILE__, __LINE__, "error", msg);
}
void MyLogger::debug(const char *msg) {
  category_.debug("file: %s  line: %d func: %s msg: %s", __FILE__, __LINE__, "debug", msg);
}
void MyLogger::info(const char *msg) {
  category_.info("file: %s  line: %d func: %s msg: %s", __FILE__, __LINE__, "info", msg);
}
MyLogger::~MyLogger() {
  Category::shutdown();
}
template<typename... Args>
void MyLogger::log(const char *msg, Args... args) {
  char tmp[256];
  memset(&tmp, 0 ,sizeof(tmp));
  sprintf(&tmp, msg, args...);
  category_.info("file: %s  line: %d func: %s msg: %s", __FILE__, __LINE__, "info", tmp);
}
//template<typename T, typename... Args>
//void Unpack(string &str,int pos,T t, Args... args) {
//  str.insert(pos, (string)t);
//  auto new_pos = str.find('%',pos);
//  if(new_pos == string::npos)
//	return;
//  str.erase(new_pos, 2);
//  Unpack(str, new_pos, args...);
//}
//template<typename T, typename... Args>
//void Unpack(string &str,int pos, T t) {
//  str.insert(pos, (string)t);
//}
//template<typename... Args>
//void MyLogger::log(const char *msg, Args... args) {
//  string str(msg);
//  auto new_pos = str.find('%',0);
//  if(new_pos == string::npos) {
//	category_.info("file: %s  line: %d func: %s msg: %s", __FILE__, __LINE__, "info", msg);
//	return;
//  }
//  str.erase(new_pos, 2);
//  Unpack(str, new_pos, args...);
//}

}

int main() {
  using namespace templateandargs;

}
