// Authors: Handling
// Created by 15870 on 2020/10/21.
// This is 

#include "InetAddress.h"
#include <cstring>
#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif
namespace netlib {

InetAddress::InetAddress(unsigned short port) {
#ifdef TEST
  cout << "InetAddress::InetAddress(unsigned short port)" << endl;
#endif
  memset(&addr_, 0, sizeof(struct sockaddr_in));
  addr_.sin_family = AF_INET;
  addr_.sin_port = htons(port);
  addr_.sin_addr.s_addr = INADDR_ANY; //默认本地ip
}
InetAddress::InetAddress(const string &ip, unsigned int port) {
#ifdef TEST
  cout << "InetAddress::InetAddress(const string &ip, unsigned int port)" << endl;
#endif
  memset(&addr_, 0, sizeof(struct sockaddr_in));
  addr_.sin_family = AF_INET;
  addr_.sin_port = htons(port);
  addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}
InetAddress::InetAddress(const sockaddr_in &sockaddr)
:addr_(sockaddr) {
#ifdef TEST
  cout << "InetAddress::InetAddress(const sockaddr_in &sockaddr)" << endl;
#endif
}
}