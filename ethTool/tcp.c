#include "tcp.h"

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