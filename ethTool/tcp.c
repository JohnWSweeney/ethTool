#include "tcp.h"

void openClientSocket(SOCKET* clientSocket, char serverIP, int portNum)
{
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		printf("WSAStartup failed with error: %d\n", result);
		return 1;
	}

	// initialize socket.
	*clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*clientSocket == INVALID_SOCKET)
	{
		printf("Client socket failed with error: %d\n", WSAGetLastError());
		return 1;
	}

	// server info.
	struct sockaddr_in serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
	//serverInfo.sin_addr.s_addr = inet_addr(serverIP);
	serverInfo.sin_port = htons(portNum);

	// connect to server.
	result = connect(*clientSocket, (SOCKADDR *)&serverInfo, sizeof(serverInfo));
	if (result == SOCKET_ERROR)
	{
		printf("Connect to server failed with error: %d\n", WSAGetLastError());
		return 1;
	}
	else // connected to server.
	{
		return 0;
	}
}

int tx(SOCKET* socket, char *buffer, int bufferLen)
{
	int result = send(*socket, buffer, bufferLen, 0);
	if (result == SOCKET_ERROR)
	{
		printf("tx.send failed with error: %d\n", WSAGetLastError());
		closesocket(*socket);
		WSACleanup();
		return 1;
	}
	else
	{
		printf("Bytes sent: %d\n", result);
		return 0;
	}
}