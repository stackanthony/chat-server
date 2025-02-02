#pragma once
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>

class ClientSocket {
private:
  int socketDescriptor;
  bool connected;

public:
  ClientSocket(const char *address, int port);
  ~ClientSocket();

  void sendMessageToServer(const std::string &message);
  bool isConnected() const { return connected; }
  int getSocketDescriptor() const { return socketDescriptor; }
  std::string readMessageFromServer();

  // Prevent copying as socket resources shouldn't be shared
  ClientSocket(const ClientSocket &) = delete;
  ClientSocket &operator=(const ClientSocket &) = delete;
};
