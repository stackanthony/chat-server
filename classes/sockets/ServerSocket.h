#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>

class ServerSocket {
private:
  int socketDescriptor;
  sockaddr_in socketAddress;

public:
  ServerSocket(int port);
  ~ServerSocket();

  int getSocketDescriptor() const { return socketDescriptor; }
  void sendMessage(const std::string &message, int clientSocketDescriptor);
};

#endif
