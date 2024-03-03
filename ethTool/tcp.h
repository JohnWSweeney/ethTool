#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

void openClientSocket(SOCKET* clientSocket, int portNum);
int tx(SOCKET* socket, char *buffer, int bufferLen);