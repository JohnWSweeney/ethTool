#include <stdio.h>
#include "commands.h"
#include "tcp.h"

int main()
{
	printf("ethTool v0.0.4\n\n");

	int result = 0;
	SOCKET clientSocket = INVALID_SOCKET;
	struct node* list = NULL;
	getCommands(&list);

	int portNum = atoi(list->next);
	openClientSocket(&clientSocket, portNum);
	
	struct node* curr = list->next->next;
	tx(&clientSocket, curr->command, (int)strlen(curr->command));

	result = shutdown(clientSocket, SD_SEND);
	printf("result: %d\n", result);

	printf("end\n");
}