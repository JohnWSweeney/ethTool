#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Ws2_32.dll") //

void openClientSocket(SOCKET* clientSocket, char serverIP, int portNum);
int tx(SOCKET* socket, char *buffer, int bufferLen);