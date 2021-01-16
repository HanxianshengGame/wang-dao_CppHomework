// Authors: Handling
// Created by 15870 on 2020/10/26.
// This is 

#include "TcpServer.h"
#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif
namespace concurrentserver {

TcpServer::TcpServer(const std::string &ip, unsigned short port)
: acceptor_(ip, port)
, loop_(acceptor_) {
#ifdef TEST
  cout << "TcpServer::TcpServer(const std::string &ip, unsigned short port)" << endl;
#endif
}
void TcpServer::Start() {
#ifdef TEST
  cout << "void TcpServer::Start()" << endl;
#endif
  acceptor_.Ready();
  loop_.Loop();
}
void TcpServer::Stop() {
#ifdef TEST
  cout << "void TcpServer::Stop()" << endl;
#endif
  loop_.UnLoop();
}
void TcpServer::SetConnectionCallback(TcpConnectionCallback &&cb) {
#ifdef TEST
  cout << "void TcpServer::SetConnectionCallback(TcpConnectionCallback &&cb)" << endl;
#endif
  loop_.set_connection_callback(std::move(cb));
}
void TcpServer::SetMessageCallback(TcpConnectionCallback &&cb) {
#ifdef TEST
  cout << "void TcpServer::SetMessageCallback(TcpConnectionCallback &&cb) " << endl;
#endif
  loop_.set_message_callback(std::move(cb));
}
void TcpServer::SetCloseCallback(TcpConnectionCallback &&cb) {
#ifdef TEST
  cout << "void TcpServer::SetCloseCallback(TcpConnectionCallback &&cb)" << endl;
#endif
  loop_.set_close_callback(std::move(cb));
}
}