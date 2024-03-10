#include <stdio.h>
#include "commands.h"
#include "tcp.h"

int main()
{
	printf("ethTool v0.0.7\n\n");

	int running = 1;
	struct node* list = NULL;
	while (running)
	{
		getCommands(&list);
		print(list);
		running = checkExit(list);
		if (running != 0)
		{
			int portNum = checkPortNum(list->next);
			printf("portNum: %d\n", portNum);
		}
	}
}