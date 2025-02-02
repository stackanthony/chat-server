#include "classes/Connection.h"
#include "classes/sockets/ServerSocket.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#ifndef SERVER_H
#define SERVER_H
bool isSocketAlive(int socket);
void handleClient(int clientSocket, ServerSocket &server);
int main();
#endif
