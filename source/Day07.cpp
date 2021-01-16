// Authors: Handling
// Created by 15870 on 2020/9/21.
// This is Log4cpp
#include <log4cpp/SimpleConfigurator.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <iostream>
using std::cout;
using std::endl;

using namespace log4cpp;
void test() {
  //日志的格式（格式化器）

   PatternLayout *ppl1 = new PatternLayout();
   ppl1->setConversionPattern("%d %c [%p] %m%n");

   PatternLayout *ppl2 = new PatternLayout();
   ppl2->setConversionPattern("%d %c [%p] %m%n");
   //日志的目的地（输出器）
   OstreamAppender *pos = new OstreamAppender("OstreamAppender", &cout);
   pos->setLayout(ppl1);

   FileAppender *prfl = new FileAppender("FileAppender", "handling.log");

   prfl->setLayout(ppl2);

   //日志记录器
   Category &root = Category::getRoot().getInstance("Mycat");
   root.addAppender(pos);
   root.addAppender(prfl);
   root.setPriority(Priority::ERROR);
  for(size_t idx = 0; idx != 300; ++idx)
  {
	root.emerg("This is an emerg message");
	root.fatal("This is an fatal message");
	root.alert("This is an alert message");
	root.crit("This is an crit message");
	root.error("This is an error message");
	root.info("This is an info message");
	root.warn("This is an warn message");
	root.notice("This is an notice message");
	root.debug("This is an debug message");
  }

  //内存回收
  Category::shutdown();


}

namespace mylog {
class MyLogger {
 public:
  void warn(const char *msg);
  void error(const char *msg);
  void debug(const char *msg);
  void info(const char *msg);
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

MyLogger::MyLogger():category_(Category::getRoot().getInstance("main_category")) {
  layout1_ = new PatternLayout();
  layout1_->setConversionPattern("%d %c [%p] %m%n");
  layout2_ = new PatternLayout();
  layout2_->setConversionPattern("%d %c [%p] %m%n");
  ostream_appender_ = new OstreamAppender("cout_appender", &cout);
  ostream_appender_->setLayout(layout1_);
  file_appender_ = new FileAppender("file_appender","handling.log");
  file_appender_->setLayout(layout2_);
  category_.addAppender(ostream_appender_);
  category_.addAppender(file_appender_);
  category_.setPriority(Priority::DEBUG);
}
void MyLogger::warn(const char *msg) {
  category_.warn("file: %s  line: %d func: %s msg: %s", __FILE__, __LINE__, "warn",msg);
}
void MyLogger::error(const char *msg) {
  category_.error("file: %s  line: %d func: %s msg: %s", __FILE__, __LINE__, "error",msg);
}
void MyLogger::debug(const char *msg) {
  category_.debug("file: %s  line: %d func: %s msg: %s", __FILE__, __LINE__, "debug",msg);
}
void MyLogger::info(const char *msg) {
  category_.info("file: %s  line: %d func: %s msg: %s", __FILE__, __LINE__, "info",msg);
}
MyLogger::~MyLogger() {
  Category::shutdown();
}
}

int main(int argc, char **argv) {
  auto my_logger = mylog::MyLogger::Instance();
  my_logger->warn("sss");
  my_logger->warn("please input:");
  my_logger->debug("sss");
  return 0;
}
