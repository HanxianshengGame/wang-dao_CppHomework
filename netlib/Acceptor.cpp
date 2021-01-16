// Authors: Handling
// Created by 15870 on 2020/10/21.
// This is 

#include "Acceptor.h"
#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif
namespace netlib {

Acceptor::Acceptor(unsigned short port)
: addr_(port),
  listen_sock_() {
#ifdef TEST
  cout << "Acceptor::Acceptor(unsigned short port)" << endl;
#endif
}
Acceptor::Acceptor(const string &ip, unsigned short port)
: addr_(ip, port),
  listen_sock_() {
#ifdef TEST
  cout << "Acceptor::Acceptor(const string &ip, unsigned short port)" << endl;
#endif
}
void Acceptor::Ready() {
#ifdef TEST
  cout << "void Acceptor::Ready()" << endl;
#endif
  SetReuseAddr(true);
  SetReusePort(true);
  Bind();
  Listen();
}

int Acceptor::Accept() {
#ifdef TEST
  cout << "int Acceptor::Accept()" << endl;
#endif
  int peerfd = ::accept(listen_sock_.fd(), nullptr, nullptr);
  if(peerfd == -1)
    perror("accept");
  return peerfd;
}
void Acceptor::SetReuseAddr(bool on) {
#ifdef TEST
  cout << "void Acceptor::SetReuseAddr(bool on)" << endl;
#endif
  int one = on;
  if(setsockopt(listen_sock_.fd(),
				SOL_SOCKET,
				SO_REUSEADDR,
				&one,
				sizeof(one)) < 0)
    perror("setsockopt");
}
void Acceptor::SetReusePort(bool on) {
#ifdef TEST
  cout << "void Acceptor::SetReusePort(bool on)" << endl;
#endif
  int one = on;
  if(setsockopt(listen_sock_.fd(),
				SOL_SOCKET,
				SO_REUSEPORT,
				&one,
				sizeof(one)) < 0)
	perror("setsockopt");
}
void Acceptor::Bind() {
#ifdef TEST
  cout << "void Acceptor::Bind()" << endl;
#endif
  int ret = ::bind(listen_sock_.fd(),
				   (struct sockaddr *)addr_.GetInetAddressPtr(),
				   	sizeof(struct sockaddr));
  if(-1 == ret)
    perror("bind");
}
void Acceptor::Listen() {
#ifdef TEST
  cout << "void Acceptor::Bind()" << endl;
#endif
  int ret = ::listen(listen_sock_.fd(), 10);
  if(-1 == ret)
    perror("listen");
}

}