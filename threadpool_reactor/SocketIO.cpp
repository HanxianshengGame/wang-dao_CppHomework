// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 

#include "SocketIO.h"
#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <sys/socket.h>
#include <algorithm>

#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif


using std::find;
namespace concurrentserver {

SocketIO::SocketIO(int fd)
: fd_(fd) {

#ifdef TEST
  cout << "SocketIO::SocketIO(int fd)" << endl;
#endif
}

int SocketIO::ReadN(char *buff, int len) const {

#ifdef TEST
  cout << "int SocketIO::ReadN(char *buff, int len) const" << endl;
#endif
  int remaining_len = len;
  char *p = buff;
  while(remaining_len > 0) {
    int ret = read(fd_, p, remaining_len);
    if(ret == -1 && errno == EINTR) {
	  continue;
    } else if(ret == -1) {
      perror("read");
      break;
    } else if(ret == 0) {
      //对端关闭
	  break;
    } else {
      remaining_len -= ret;
      p += ret;
    }
  }
  return len - remaining_len;
}

int SocketIO::ReadLine(char *buff, int max_len) {
#ifdef TEST
  cout << "int SocketIO::ReadLine(char *buff, int max_len)" << endl;
#endif
  int remaining = max_len - 1;
  char *p = buff;
  int ret;
  int total = 0;
  while (remaining > 0) {
    ret = RecvPeek(p, remaining);
    //返回值处理 TODO
    //查找换行 '\n'
    auto pret = find(p, p+ret, '\n');
    if(pret != (p+ret)) {
      auto sz = (pret - p) + 1;
      ReadN(p, sz);
      total += sz;
      p += sz;
      *p = '\0';
	  return total;
    }
    ReadN(p, ret);
	remaining -= ret;
	p += ret;
	total += ret;
  }
  *p = '\0';  //最终没有发现'\n'
  return total;
}
int SocketIO::WriteN(const char *buff, int len) const {
#ifdef TEST
  cout << "int SocketIO::WriteN(const char *buff, int len) const" << endl;
#endif
  int remaining_len = len;
  const char *p = buff;
  while (remaining_len > 0) {
    int ret = write(fd_, p, remaining_len);
    if(ret == -1 && errno == EINTR) {
	  continue;
    } else if(ret == -1) {
      // 极大可能对端关闭
      perror("write");
	  break;
    } else {
      remaining_len -= ret;
      p += ret;
    }
  }
  return len - remaining_len;
}
int SocketIO::RecvPeek(char *buff, int len) const {
#ifdef TEST
  cout << "int SocketIO::RecvPeek(char *buff, int len) const" << endl;
#endif
  int ret;
  do {
    ret = recv(fd_, buff, len, MSG_PEEK);
  } while (ret == -1 && errno == EINTR);
  return ret;
}
}
