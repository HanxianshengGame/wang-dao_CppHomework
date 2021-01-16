// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 

#include "TcpConnection.h"
#include <cerrno>
#include <sstream>
#include "EventLoop.h"

#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif


namespace concurrentserver {

TcpConnection::TcpConnection(int fd, EventLoop *loop)
: loop_(loop)
, sock_(fd)
, sock_io_(fd)
, local_addr_(local_addr())
, peer_addr_(peer_addr())
, is_shutdown_write_(false)

{

#ifdef TEST
  cout << "TcpConnection::TcpConnection(int fd, EventLoop *loop)" << endl;
#endif
}
TcpConnection::~TcpConnection() {
#ifdef TEST
  cout << "TcpConnection::~TcpConnection()" << endl;
#endif
  if(!is_shutdown_write_)
    ShutDown();
}
std::string TcpConnection::Receive() {
#ifdef TEST
  cout << "std::string TcpConnection::Receive()" << endl;
#endif
  char buff[65536] = {0};
  sock_io_.ReadLine(buff, sizeof(buff));
  return std::string(buff);
}
void TcpConnection::Send(const std::string &msg) {
#ifdef TEST
  cout << "void TcpConnection::Send(const std::string &msg) " << endl;
#endif
  sock_io_.WriteN(msg.c_str(), msg.size());
}
void TcpConnection::SendInLoop(const std::string &msg) {
#ifdef TEST
  cout << "void TcpConnection::SendInLoop(const std::string &msg)" << endl;
#endif
  if(loop_) {
    loop_->RunInLoop(std::bind(&TcpConnection::Send, this, std::ref(msg)));
  }
}
std::string TcpConnection::ToString() const {
#ifdef TEST
  cout << "std::string TcpConnection::ToString() const" << endl;
#endif
  std::ostringstream  oss;
  oss << local_addr_.ip() << ":" << local_addr_.port() <<" --> "
      << peer_addr_.ip() << ":" << peer_addr_.port();
  return oss.str();
}
void TcpConnection::ShutDown() {
#ifdef TEST
  cout << "void TcpConnection::ShutDown() " << endl;
#endif
  if(!is_shutdown_write_) {
    is_shutdown_write_ = true;
    sock_.ShutDownWrite(); //断开处理
  }
}
InetAddress TcpConnection::local_addr() const {
#ifdef TEST
  cout << "InetAddress TcpConnection::local_addr() const " << endl;
#endif
  struct sockaddr_in addr{};
  socklen_t len = sizeof(struct sockaddr);
  if(getsockname(sock_.fd(),
				 (struct sockaddr *)&addr,
				 &len) == -1)
    perror("getsockname");

  return InetAddress(addr);
}

InetAddress TcpConnection::peer_addr() const {
#ifdef TEST
  cout << "InetAddress TcpConnection::peer_addr() const" << endl;
#endif
  struct sockaddr_in addr{};
  socklen_t len = sizeof(struct sockaddr);
  if(getpeername(sock_.fd(),
				 (struct sockaddr *)&addr,
				 &len) == -1)
	perror("getsockname");

  return InetAddress(addr);
}

void TcpConnection::set_connection_callback(const TcpConnectionCallback &cb) {
#ifdef TEST
  cout << "void TcpConnection::set_connection_callback(const TcpConnectionCallback &cb)" << endl;
#endif
  connection_callback_ = cb;
}
void TcpConnection::set_message_callback(const TcpConnectionCallback &cb) {
#ifdef TEST
  cout << "void TcpConnection::set_message_callback(const TcpConnectionCallback &cb)" << endl;
#endif
  message_callback_ = cb;
}
void TcpConnection::set_close_callback(const TcpConnectionCallback &cb) {
#ifdef TEST
  cout << "void TcpConnection::set_close_callback(const TcpConnectionCallback &cb)" << endl;
#endif
  close_callback_ = cb;
}
bool TcpConnection::IsConnectionClosed() {
#ifdef TEST
  cout << "bool TcpConnection::IsConnectionClosed()" << endl;
#endif
  int nready = -1;
  char buff[128] = {0};
  do {
    nready = recv(sock_.fd(), buff, sizeof(buff), MSG_PEEK);
  }while(nready == -1 && errno == EINTR);

  return nready == 0;
}
void TcpConnection::HandleConnectionCallback() {
#ifdef TEST
  cout << "void TcpConnection::HandleConnectionCallback()" << endl;
#endif
  if(connection_callback_) {
    connection_callback_(shared_from_this());
  }
}
void TcpConnection::HandleMessageCallback() {
#ifdef TEST
  cout << "void TcpConnection::HandleMessageCallback()" << endl;
#endif
  if(message_callback_) {
    message_callback_(shared_from_this());
  }
}
void TcpConnection::HandleCloseCallback() {
#ifdef TEST
  cout << "void TcpConnection::HandleCloseCallback()" << endl;
#endif
  if(close_callback_) {
    close_callback_(shared_from_this());
  }
}
}