#include "ServerSocket.h"
#include <string>
#include <sys/socket.h>

ServerSocket::ServerSocket(int port) {
  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketDescriptor < 0) {
    throw std::runtime_error("Failed to create socket");
  }

  socketAddress.sin_family = AF_INET;
  socketAddress.sin_port = htons(port);
  socketAddress.sin_addr.s_addr = INADDR_ANY;

  int err = bind(socketDescriptor, (struct sockaddr *)&socketAddress,
                 sizeof(socketAddress));
  if (err < 0) {
    const std::string error_message =
        "Failed to bind socket: " + std::to_string(err);
    throw std::runtime_error(error_message);
  }

  if (listen(socketDescriptor, 3) < 0) {
    throw std::runtime_error("Error listening on socket");
  }

  std::cout << "Server is listening on port " << port << std::endl;
}

void ServerSocket::sendMessage(const std::string &message,
                               int clientSocketDescriptor) {
  ssize_t bytesSent =
      send(clientSocketDescriptor, message.c_str(), message.length(), 0);
  if (bytesSent < 0) {
    throw std::runtime_error("Failed to send message to client" +
                             std::to_string(clientSocketDescriptor));
  }
}

ServerSocket::~ServerSocket() { shutdown(socketDescriptor, SHUT_RDWR); }
