// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 

#include "InetAddress.h"
#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif

namespace concurrentserver {

InetAddress::InetAddress(unsigned short port) {
#ifdef TEST
  cout << "InetAddress::InetAddress(unsigned short port) " << endl;
#endif
  addr_.sin_family = AF_INET;
  addr_.sin_port = htons(port);
  addr_.sin_addr.s_addr = INADDR_ANY;
}
InetAddress::InetAddress(const std::string &ip, unsigned short port) {
#ifdef TEST
  cout << "InetAddress::InetAddress(const std::string &ip, unsigned short port)" << endl;
#endif
  addr_.sin_family = AF_INET;
  addr_.sin_port = htons(port);
  addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}
InetAddress::InetAddress(const sockaddr_in &addr)
: addr_(addr) {
#ifdef TEST
  cout << "InetAddress::InetAddress(const sockaddr_in &addr)" << endl;
#endif
}
}