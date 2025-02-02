#include "Connection.h"
Connection::Connection(int serverDescriptor) {
  connectionDescriptor = accept(serverDescriptor, nullptr, nullptr);
  if (connectionDescriptor < 0) {
    throw std::runtime_error("Error accepting connection");
  }
  std::cout << "New connection established" << std::endl;
}

std::string Connection::readMessage() {
  char buffer[1024] = {0};

  ssize_t bytesRead = recv(connectionDescriptor, buffer, sizeof(buffer) - 1, 0);
  if (bytesRead < 0) {
    throw std::runtime_error("Error reading from socket");
  }
  if (bytesRead == 0) {
    throw std::runtime_error("Client disconnected");
  }

  return std::string(buffer);
}
