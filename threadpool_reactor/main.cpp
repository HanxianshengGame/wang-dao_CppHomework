// Authors: Handling
// Created by 15870 on 2020/10/26.
// This is 启动程序

#include "TcpServer.h"
#include "ThreadPool.h"


#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using concurrentserver::ThreadPool;
using concurrentserver::TcpConnectionPtr;
using concurrentserver::TcpServer;
ThreadPool *unique_threadpool = nullptr;
class WorkTask {
 public:
  WorkTask(string msg, TcpConnectionPtr conn)
  : msg_(std::move(msg))
  , conn_(std::move(conn))
  {}

  //由一个线程池中的子线程进行的
  void Process() {
	//业务逻辑的处理，交给线程池进行
	//
	//(关键字推荐)
	//  hello -->  hello/ helloworld
	//decode
	//compute    // threadName --> 缓存
	//encode
	//
	string response;
	//当拿到了返回结果时，不能直接在这里发送，因为此时还在计算线程；
	//这不是计算线程的职责； 按照我们的设计，数据的发送是IO线程来进行的
	//所以在这里要通知IO线程进行发送
	//_conn->send(response);  //要将该语句看成是一个回调函数，注册给IO线程
	cout << concurrentserver::current_thread::name << endl;
	conn_->SendInLoop(msg_);
  }
 private:
  string msg_;
  TcpConnectionPtr conn_;
};
void OnConnection(const TcpConnectionPtr &conn) {
  cout << ">>" << conn->ToString() << " has connected! " << endl;
  conn->Send("welcome to server!");
}

void OnMessage(const TcpConnectionPtr &conn) {
  string msg = conn->Receive();
  cout << ">>> receive: " << msg << endl;
  //回显操作
  //conn->send(msg);

  //得到了要交给客户端的结果, 此时如果业务的处理时间较长，就不适合在IO线程
  //直接处理；
  //
  //应该将收到的数据封装成一个任务，交给线程池进行处理

  WorkTask task(msg, conn);
  unique_threadpool->AddTask(std::bind(&WorkTask::Process, task));
}

void OnClose(const TcpConnectionPtr &conn) {
  cout << "> " << conn->ToString() << "has closed!" << endl;
}

class EchoServer {
 public:
  EchoServer(const string &ip, unsigned short port)
  : thread_pool_(4, 10)
  , tcp_server_(ip,port) {
  }

  void Start() {
    thread_pool_.Start();
	unique_threadpool = &thread_pool_;
	tcp_server_.SetConnectionCallback(OnConnection);
	tcp_server_.SetMessageCallback(OnMessage);
	tcp_server_.SetCloseCallback(OnClose);

	tcp_server_.Start();
  }

 private:
  ThreadPool thread_pool_;
  TcpServer  tcp_server_;
};




int main(int argc, char **argv) {
  EchoServer server("172.17.47.226", 2000);
  server.Start();
  return 0;
}
