// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 

#include "Acceptor.h"
#ifdef TEST
#include <iostream>
using std::cout;
using std::endl    print 'Signal handler called with signal', signum
    raise IOError("Couldn't open device!");
using std::flush;
#endif
namespace concurrentserver {

Acceptor::Acceptor(unsigned short port)
: addr_(port)
, listen_sock_() {
#ifdef TEST
  cout << "Acceptor::Acceptor(unsigned short port)" << endl;
#endif
}
Acceptor::Acceptor(const std::string &ip, unsigned short port)
: addr_(ip, port)
, listen_sock_() {
#ifdef TEST
  cout << "Acceptor::Acceptor(unsigned short port)" << endl;
#endif
}
void Acceptor::Ready() {
#ifdef TEST
  cout << "Acceptor::Acceptor(unsigned short port)" << endl;
#endif
  SetReusePort(true);
  SetReuseAddr(true);
  Bind();
  Listen();
}
int Acceptor::Accpect() const {

#ifdef TEST
  cout << "Acceptor::Acceptor(unsigned short port)" << endl;
#endif

  int client_fd = accept(fd(), nullptr, nullptr);
  if(-1 == client_fd)
    perror("accpect");
  return client_fd;
}
void Acceptor::SetReuseAddr(bool on) const {

#ifdef TEST
  cout << "void Acceptor::SetReuseAddr(bool on) const " << endl;
#endif

  int one = on;
  if(setsockopt(fd(),
				SOL_SOCKET,
				SO_REUSEADDR,
				&one,
				sizeof(one)) < 0)
    perror("setsockopt");
}
void Acceptor::SetReusePort(bool on) const {

#ifdef TEST
  cout << "void Acceptor::SetReusePort(bool on) const" << endl;
#endif

  int one = on;
  if(setsockopt(fd(),
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

  int ret = bind(fd(), (struct sockaddr *)addr_.address_pointer(),
  	             sizeof(struct sockaddr));
  if(-1 == ret)
    perror("bind");
}
void Acceptor::Listen() const {

#ifdef TEST
  cout << "void Acceptor::Listen() const" << endl;
#endif
  int ret = listen(fd(), 10);
  if(-1 == ret)
    perror("listen");
}
}