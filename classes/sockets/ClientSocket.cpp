#include "ClientSocket.h"
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

ClientSocket::ClientSocket(const char *address, int port) : connected(false) {
  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketDescriptor < 0) {
    throw std::runtime_error("Failed to create socket");
  }

  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);

  if (inet_pton(AF_INET, address, &serverAddr.sin_addr) <= 0) {
    close(socketDescriptor);
    throw std::runtime_error("Invalid address");
  }

  if (connect(socketDescriptor, (struct sockaddr *)&serverAddr,
              sizeof(serverAddr)) < 0) {
    close(socketDescriptor);
    throw std::runtime_error("Connection failed");
  }

  connected = true;
  std::cout << "Connected to server at " << address << ":" << port << std::endl;
}

ClientSocket::~ClientSocket() {
  if (socketDescriptor >= 0) {
    close(socketDescriptor);
  }
}

void ClientSocket::sendMessage(const std::string &message,
                               int clientSocketDescriptor) {
  if (!connected) {
    throw std::runtime_error("Not connected to server");
  }

  std::string new_message =
      "[" + std::to_string(clientSocketDescriptor) + "] " + message;
  ssize_t bytesSent =
      send(socketDescriptor, new_message.c_str(), new_message.length(), 0);
  if (bytesSent < 0) {
    connected = false;
    throw std::runtime_error("Failed to send message");
  }
}

std::string ClientSocket::readMessage() {
  char buffer[1024] = {0};
  ssize_t bytesRead = recv(socketDescriptor, buffer, sizeof(buffer) - 1, 0);

  if (bytesRead < 0) {
    throw std::runtime_error("Error reading from socket");
  }
  if (bytesRead == 0) {
    throw std::runtime_error("Server disconnected");
  }

  return std::string(buffer);
}
