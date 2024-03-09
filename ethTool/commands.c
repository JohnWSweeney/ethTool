#include "commands.h"

void checkServerIP(struct node* list)
{
	if (list->command == "host")
	{
		strcpy_s(list->command, sizeof(list->command), "127.0.0.1");
		printf("boop\n");
	}
}

int checkPortNum(struct node* list)
{
	int result = atoi(list->next);
	if (result == 0)
	{
		printf("Invalid port number.\n");
	}
	return result;
}

void getCommands(struct node** list)
{
	int result = 0;

	do {
		clear(list);

		// get input.
		char str[123];
		do {
			fgets(str, sizeof(str), stdin);
		} while (str[0] == '\n');

		// tokenize input.
		int i = 0;
		int j = 0;
		char temp[123];
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '\n')
			{
				temp[j] = str[i];
				++j;
			}
			else if (str[i] == ' ')
			{
				temp[j] = '\0';
				addBack(list, temp);
				memset(temp, 0, sizeof(temp));
				j = 0;
			}
			++i;
		}
		addBack(list, temp);

		checkServerIP(*list);
		result = checkPortNum(*list);

	} while (result == 0);
}