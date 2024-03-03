#include <stdio.h>
#include <stdlib.h>
#include "tcp.h"

int main()
{
	printf("ethTool v0.0.3\n\n");

	int result = 0;
	SOCKET clientSocket = INVALID_SOCKET;
	int portNum = 1234;
	openClientSocket(&clientSocket, portNum);

	const char *sendbuf = "the quick brown fox jumped over the lazy dog";
	tx(&clientSocket, sendbuf, (int)strlen(sendbuf));
	

	result = shutdown(clientSocket, SD_SEND);
	printf("result: %d\n", result);

	printf("end\n");
}