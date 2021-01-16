// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 

#include "Socket.h"
#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>

#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif

namespace concurrentserver {

Socket::Socket() {
#ifdef TEST
  cout << "Socket::Socket() " << endl;
#endif
  fd_ = socket(AF_INET, SOCK_STREAM, 0);
  if(fd_ == -1)
    perror("socket");
}
Socket::Socket(const int fd)
:fd_(fd) {
#ifdef TEST
  cout << "Socket::Socket(const int fd) " << endl;
#endif

}
Socket::~Socket() {
#ifdef TEST
  cout << "Socket::~Socket() " << endl;
#endif
  close(fd_);
}
void Socket::ShutDownWrite() const {
#ifdef TEST
  cout << "void Socket::ShutDownWrite() const " << endl;
#endif
  shutdown(fd_, SHUT_WR);
}
}