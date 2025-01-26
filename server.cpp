#include "server.h"
// server.cpp
int main(int argc, char *argv[]) {
  ServerSocket server(8080);
  std::cout << "Server started on port 8080" << std::endl;
  while (true) {
    try {
      Connection conn(server.getSocketDescriptor());
      std::string clientMessage = conn.readMessage();
      std::cout << "Received message: " << clientMessage << std::endl;

      server.sendMessage(clientMessage, conn.getDescriptor());

    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  return 0;
}
