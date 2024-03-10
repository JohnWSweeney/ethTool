#include "commands.h"

int checkExit(struct node* list)
{
	int result = strcmp(list->command, "exit");
	if (result == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void checkServerIP(struct node* list)
{
	if (list->command == "host")
	{
		strcpy_s(list->command, sizeof(list->command), "127.0.0.1");
	}
}

int checkPortNum(struct node* list)
{
	if (list == NULL) return -1;
	int result = atoi(list->command);
	if (result == 0)
	{
		printf("Invalid port number.\n");
		return 0;
	}
	else
	{
		return result;
	}
}

void getCommands(struct node** list)
{
	int result = 0;
	do {
		clear(list); // clear previous commands.
		// get input.
		char str[123]; // input string.
		do {
			fgets(str, sizeof(str), stdin);
		} while (str[0] == '\n');

		// tokenize input.
		int i = 0; // input string index.
		int j = 0; // temp string index.
		char temp[123]; // temp string.
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
		temp[j] = '\0';
		addBack(list, temp);
		result = isEmpty(list);
	} while (result);
}