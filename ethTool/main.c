#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

void openClientSocket(SOCKET* clientSocket, int portNum)
{
	WSADATA wsaData;
	struct addrinfo *host = NULL, *ptr = NULL, hints; //--

	int result = 0;
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		printf("WSAStartup failed with error: %d\n", result);
	}

	*clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*clientSocket == INVALID_SOCKET)
	{
		printf("error: %d", WSAGetLastError());
	}
	else
	{
		printf("socket success.\n");
	}

	// server info.
	ZeroMemory(&hints, sizeof(hints));
	//memset(&hints, sizeof(hints))
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	char portNumStr[16];
	sprintf_s(portNumStr, sizeof(portNumStr), "%d", portNum);

	result = getaddrinfo(NULL, portNumStr, &hints, &host);
	if (result != 0)
	{
		WSACleanup();
		printf("broke dat\n");
	}

	for (ptr = host; ptr != NULL; ptr = ptr->ai_next)
	{
		*clientSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (*clientSocket == INVALID_SOCKET)
		{
			printf("err: %d\n", WSAGetLastError());
			WSACleanup();
		}

		result = connect(*clientSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (result != SOCKET_ERROR)
		{
			printf("connected to server.\n");
			continue;
		}
		break;
	}

	freeaddrinfo(host);

	if (*clientSocket == INVALID_SOCKET)
	{
		printf("can't connect to server.\n");
		WSACleanup();
	}
	else
	{
		printf("clientSocket good.\n");
	}
}

int main()
{
	printf("ethTool v0.0.2\n\n");

	int result = 0;
	SOCKET clientSocket = INVALID_SOCKET;
	int portNum = 1234;
	openClientSocket(&clientSocket, portNum);

	const char *sendbuf = "the quick brown fox jumped over the lazy dog";
	result = send(clientSocket, sendbuf, (int)strlen(sendbuf), 0);
	printf("bytes sent: %d\n", result);

	result = shutdown(clientSocket, SD_SEND);
	printf("result: %d\n", result);

	printf("end\n");
}