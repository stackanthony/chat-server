#include "client.h"
int main() {
  try {
    ClientSocket client("127.0.0.1", 8080);
    client.sendMessage("Hello server!", client.getSocketDescriptor());
    
    while (true) {
      try {
        std::string message = client.readMessage();
        std::cout << "Received: " << message << std::endl;
      } catch (const std::exception& e) {
        std::cerr << "Read error: " << e.what() << std::endl;
        break; 
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
