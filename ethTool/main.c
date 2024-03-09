#include <stdio.h>
#include "commands.h"
#include "tcp.h"

int main()
{
	printf("ethTool v0.0.6\n\n");

	int result = 0;
	SOCKET clientSocket = INVALID_SOCKET;
	struct node* list = NULL;
	while (1)
	{
		getCommands(&list);

		int portNum = atoi(list->next);
		char serverIP[] = "127.0.0.1";
		openClientSocket(&clientSocket, serverIP, portNum);

		struct node* curr = list->next->next;
		tx(&clientSocket, curr->command, (int)strlen(curr->command));

		result = shutdown(clientSocket, SD_SEND);
		printf("\n\n");
	}
}