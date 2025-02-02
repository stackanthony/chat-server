#include "client.h"
int main() {
  try {
    ClientSocket client("127.0.0.1", 8080);

    int option;
    std::cout
        << "Choose an option:\n1. Send message\n2. Listen to message\nOption: ";
    std::cin >> option;
    std::cin.ignore(); // INFO: ignores newline in input buffer

    switch (option) {
    case 1: {
      while (true) {
        std::string message;
        std::cout << "Enter message to send to server: ";
        std::getline(std::cin, message);
        if (message == "exit") {
          break;
        }
        client.sendMessageToServer(message);
      }
    } break;

    case 2:
      while (true) {
        std::string receivedMessage = client.readMessageFromServer();
        std::cout << "Received: " << receivedMessage << std::endl;
      }
      break;

    default:
      std::cout << "Invalid option." << std::endl;
      break;
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
