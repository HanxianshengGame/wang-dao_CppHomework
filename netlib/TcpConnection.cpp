// Authors: Handling
// Created by 15870 on 2020/10/21.
// This is 

#include "TcpConnection.h"
#include "InetAddress.h"
#include <cerrno>
#include <cstdlib>
#include <sys/socket.h>
#include <sstream>
#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif
namespace netlib {
TcpConnection::TcpConnection(int fd)
: sock_(fd),
  sock_io_(fd),
  local_addr(GetLocalAddr(fd)),
  peer_addr(GetPeerAddr(fd)),
  is_shutdown_write_(false) {
#ifdef TEST
  cout << "TcpConnection::TcpConnection(int fd)" << endl;
#endif
}
TcpConnection::~TcpConnection() {
#ifdef TEST
  cout << "TcpConnection::~TcpConnection()" << endl;
#endif
  if(!is_shutdown_write_)
    ShutDown();
}

string TcpConnection::Receive() {
#ifdef TEST
  cout << "string TcpConnection::Receive() " << endl;
#endif
  char buff[65536] = {0};
  int ret = sock_io_.ReadLine(buff, sizeof(buff));
  if(ret == -1)
    HandleCloseCallback();
  return string(buff);
}

void TcpConnection::Send(const string &msg) {
#ifdef TEST
  cout << "void TcpConnection::Send(const string &msg)" << endl;
#endif
  sock_io_.WriteN(msg.c_str(), msg.size());
}
string TcpConnection::ToString() const {
#ifdef TEST
  cout << "string TcpConnection::ToString() const" << endl;
#endif
  std::ostringstream oss;
  oss << local_addr.ip() << ":" << local_addr.port() << " -->"
      << peer_addr.ip() << ":" << peer_addr.port();
  return oss.str();
}
void TcpConnection::ShutDown() {
#ifdef TEST
  cout << "void TcpConnection::ShutDown()" << endl;
#endif
  if(!is_shutdown_write_) {
    is_shutdown_write_ = true;
    sock_.ShutDownWrite();
  }
}
void TcpConnection::SetConnectionCallback(const netlib::TcpConnectionCallback &cb) {
#ifdef TEST
  cout << "void TcpConnection::SetConnectionCallback(const netlib::TcpConnectionCallback &cb)" << endl;
#endif
  on_connection_ = cb;
}
void TcpConnection::SetMessageCallback(const netlib::TcpConnectionCallback &cb) {
#ifdef TEST
  cout << "void TcpConnection::SetMessageCallback(const netlib::TcpConnectionCallback &cb)" << endl;
#endif
  on_message_ = cb;
}
void TcpConnection::SetCloseCallback(const netlib::TcpConnectionCallback &cb) {
#ifdef TEST
  cout << "void TcpConnection::SetCloseCallback(const netlib::TcpConnectionCallback &cb)" << endl;
#endif
  on_close_ = cb;
}
void TcpConnection::HandleConnectionCallback() {
#ifdef TEST
  cout << "void TcpConnection::HandleConnectionCallback()" << endl;
#endif
 if(on_connection_)
   on_connection_(shared_from_this());
}
void TcpConnection::HandleMessageCallback() {
#ifdef TEST
  cout << "void TcpConnection::HandleMessageCallback()" << endl;
#endif
  if(on_message_)
    on_message_(shared_from_this());
}
void TcpConnection::HandleCloseCallback() {
#ifdef TEST
  cout << "void TcpConnection::HandleCloseCallback()" << endl;
#endif
  if(on_close_)
    on_close_(shared_from_this());
}

bool TcpConnection::IsConnectionClose() {
#ifdef TEST
  cout << "bool TcpConnection::IsConnectionClose()" << endl;
#endif
  int nready = -1;
  char buff[128] = {0};
  do {
    nready = ::recv(sock_.fd(), buff, sizeof(buff), MSG_PEEK);
  } while(nready == -1  && errno == EINTR);
  return nready == 0;
}
InetAddress TcpConnection::GetLocalAddr(const int fd) {
#ifdef TEST
  cout << "InetAddress TcpConnection::GetLocalAddr(const int fd)" << endl;
#endif
  struct sockaddr_in addr{};
  socklen_t len = sizeof(struct sockaddr);
  if(getsockname(sock_.fd(), (struct sockaddr*)&addr, &len) == -1)
	perror("getsockname");
  return InetAddress(addr);
}
InetAddress netlib::TcpConnection::GetPeerAddr(const int fd) {
#ifdef TEST
  cout << "InetAddress netlib::TcpConnection::GetPeerAddr(const int fd)" << endl;
#endif
  struct sockaddr_in addr{};
  socklen_t len = sizeof(struct sockaddr);
  if(getpeername(sock_.fd(), (struct  sockaddr*)&addr, &len) == -1)
    perror("getpeername");
  return InetAddress(addr);
}

}