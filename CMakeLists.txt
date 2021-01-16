cmake_minimum_required(VERSION 3.10.2)
project(CppHomeWork)

set(CMAKE_CXX_STANDARD 11)
include_directories(CppHomeWork log4cpp/include)
link_directories(CppHomeWork log4cpp/src)
#add_executable(CppHomeWork netlib/InetAddress.cpp
#        netlib/Socket.cpp
#        netlib/SocketIO.cpp
#        netlib/Acceptor.cpp
#        netlib/TcpConnection.cpp
#        netlib/EventLoop.cpp
#        netlib/TcpServer.cpp
#        netlib/main.cpp netlib/test_client/client.cpp netlib/test_server/server.cpp netlib/Eventfd.cpp netlib/Eventfd.h)

add_executable(CppHomeWork  threadpool_reactor/main.cpp)