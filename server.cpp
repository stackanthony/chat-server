#include "server.h"

std::vector<int> clientSockets;
std::mutex clientsMutex;

bool isSocketAlive(int socket) {
  char buffer[1];
  int result = recv(socket, buffer, 1, MSG_PEEK | MSG_DONTWAIT);

  if (result == 0) {
    // Connection closed by peer
    return false;
  }
  if (result < 0) {
    // Check if error is expected (would block means socket is still alive)
    return (errno == EAGAIN || errno == EWOULDBLOCK);
  }
  return true;
}
void handleClient(int clientSocket, ServerSocket &server) {
  try {
    while (true) {

      if (!isSocketAlive(clientSocket)) {
        std::cout << "Client " << clientSocket << " disconnected" << std::endl;
        std::lock_guard<std::mutex> lock(clientsMutex);
        auto it =
            std::find(clientSockets.begin(), clientSockets.end(), clientSocket);
        if (it != clientSockets.end()) {
          clientSockets.erase(it);
        }
        close(clientSocket);
        break;
      }
      char buffer[1024] = {0};
      ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

      if (bytesRead <= 0) {
        break; // Client disconnected
      }

      std::string message(buffer, bytesRead);
      std::cout << "Received: " << message << std::endl;

      // Broadcast to all other clients
      std::lock_guard<std::mutex> lock(clientsMutex);
      for (int otherSocket : clientSockets) {
        if (otherSocket != clientSocket) {
          server.sendMessage(message, otherSocket);
        }
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Client handler error: " << e.what() << std::endl;
  }

  // Remove client socket from list
  std::lock_guard<std::mutex> lock(clientsMutex);
  clientSockets.erase(
      std::remove(clientSockets.begin(), clientSockets.end(), clientSocket),
      clientSockets.end());
  close(clientSocket);
}

int main() {
  ServerSocket server(8080);
  std::cout << "Server started on port 8080" << std::endl;

  while (true) {
    try {
      // Accept new connection
      int clientSocket = accept(server.getSocketDescriptor(), nullptr, nullptr);
      if (clientSocket < 0) {
        continue;
      }

      // Add to clients list
      {
        std::lock_guard<std::mutex> lock(clientsMutex);
        clientSockets.push_back(clientSocket);
      }

      // Create thread to handle client
      std::thread(handleClient, clientSocket, std::ref(server)).detach();

    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  return 0;
}
