// Authors: Handling
// Created by 15870 on 2020/10/21.
// This is 

#include "SocketIO.h"
#include <cstdio>
#include <unistd.h>
#include <cerrno>
#include <sys/socket.h>

#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif

namespace netlib {

SocketIO::SocketIO(const int fd)
	: fd_(fd) {
#ifdef TEST
  cout << "SocketIO::SocketIO(const int fd)" << endl;
#endif
}
int SocketIO::ReadN(char *buff, const int len) const {
#ifdef TEST
  cout << "int SocketIO::ReadN(char *buff, const int len) const " << endl;
#endif
  int remaining_len = len; //剩余读取字节数
  char *curbuff_pos = buff;
  while (remaining_len > 0) {
	int ret = ::read(fd_, curbuff_pos, remaining_len);
	if (ret == -1 && errno == EINTR) { //系统调用中断
	  continue;
	} else if (ret == -1) {      //非系统调用中断导致的错误
	  perror("read");
	  break;
	} else if (ret == 0) {
	  break;
	} else {
	  remaining_len -= ret;
	  curbuff_pos += ret;
	}
  }
  return len - remaining_len;
}

int SocketIO::ReadLine(char *buff, const int max_len) const {
#ifdef TEST
  cout << "int SocketIO::ReadLine(char *buff, const int max_len) const" << endl;
#endif
  int remaining_len = max_len - 1;
  char *curbuff_pos = buff;
  int ret;
  int total = 0;
  while(remaining_len > 0) {
    ret = RecvPeek(curbuff_pos, remaining_len);
#ifdef TEST
    cout << "ret:" << ret << endl;
#endif
    if(ret == 0) {
      //对端关闭
      return -1;
    }
    //查找一个\n
    for(int idx = 0; idx != ret; ++idx) {
      if(curbuff_pos[idx] == '\n') {
        int sz = idx + 1;
        ReadN(curbuff_pos, sz);
        total += sz;
        curbuff_pos += sz;
        *curbuff_pos = '\0';
        return total;
      }
    }
    ReadN(curbuff_pos, ret);
    remaining_len -= ret;
    curbuff_pos += ret;
    total += ret;
  }
  *curbuff_pos = '\0';
  return total;
}
int SocketIO::WriteN(const char *buff, const int len) const {
#ifdef TEST
  cout << "int SocketIO::WriteN(const char *buff, const int len) const" << endl;
#endif
  int remaining_len = len;
  const char *curbuff_pos = buff;
  while(remaining_len > 0) {
    int ret = ::write(fd_, curbuff_pos, remaining_len);
    if(ret == -1 && errno == EINTR) {
	  continue;
    } else if(ret == -1) {
      perror("write");
      break;
    } else {
      remaining_len -= ret;
      curbuff_pos += ret;
    }
  }
  return len - remaining_len;
}
int SocketIO::RecvPeek(char *buff, const int len) const {
#ifdef TEST
  cout << "int SocketIO::RecvPeek(char *buff, const int len) const " << endl;
#endif
  int ret;
  do {
      ret = recv(fd_, buff, len, MSG_PEEK);
  } while (ret == -1 && errno == EINTR);
  return ret;
}
}
