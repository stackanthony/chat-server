#include <iostream>
#include <sys/socket.h>
class Connection {
private:
  int connectionDescriptor;

public:
  Connection(int serverDescriptor);
  int getDescriptor() const { return connectionDescriptor; }
  std::string readMessage();
};
