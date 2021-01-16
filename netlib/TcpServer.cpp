// Authors: Handling
// Created by 15870 on 2020/10/22.
// This is 

#include "TcpServer.h"

#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif
namespace netlib {

TcpServer::TcpServer(const string &ip, unsigned short port)
: acceptor_(ip, port)
, loop_(acceptor_) {
#ifdef TEST
  cout << "TcpServer::TcpServer(const string &ip, unsigned short port)" << endl;
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
void TcpServer::set_connection_callback(TcpConnectionCallback &&cb) {
#ifdef TEST
  cout << "void TcpServer::set_connection_callback(TcpConnectionCallback &&cb) " << endl;
#endif
  loop_.set_on_connection_callback(std::move(cb));
}
void TcpServer::set_message_callback(TcpConnectionCallback &&cb) {
#ifdef TEST
  cout << "void TcpServer::set_message_callback(TcpConnectionCallback &&cb)" << endl;
#endif
  loop_.set_on_message_callback(std::move(cb));
}
void TcpServer::set_close_callback(TcpConnectionCallback &&cb) {

#ifdef TEST
  cout << "void TcpServer::set_close_callback(TcpConnectionCallback &&cb) " << endl;
#endif
  loop_.set_on_close_callback(std::move(cb));
}
}