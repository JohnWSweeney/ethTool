#include "singlyLinkedList.h"

int init(struct node** list, char* command)
{
	struct node* newNode = malloc(sizeof(struct node));
	if (newNode != NULL)
	{
		memcpy(newNode->command, command, sizeof(newNode->command));
		newNode->next = NULL;
		*list = newNode;
		return 0;
	}
	else
	{
		printf("Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
}

int addBack(struct node** list, char* command)
{
	if (*list == NULL)
	{
		init(list, command);
		return 0;
	}

	struct node* head = *list;
	while (*list != NULL)
	{
		struct node* curr = *list;
		if (curr->next == NULL)
		{
			struct node* newNode = malloc(sizeof(struct node));
			if (newNode != NULL)
			{
				memcpy(newNode->command, command, sizeof(newNode->command));
				curr->next = newNode;
				newNode->next = NULL;
				*list = head;
				return 0;
			}
			else
			{
				printf("Memory allocation failed.\n");
				exit(EXIT_FAILURE);
			}
		}
		*list = curr->next;
	}
}

int clear(struct node**list)
{
	if (*list == NULL) return 1; // list is empty.

	while (*list != NULL)
	{
		struct node* dummy = *list;
		*list = dummy->next;
		free(dummy);
	}
	return 0;
}

int isEmpty(struct node* list)
{
	if (list == NULL) return 1;
	else return 0;
}

int print(struct node* list)
{
	if (list == NULL) return 1; // list is empty.

	printf("cmd:\tcurr:\t\t\tnext:\n");
	while (list != NULL)
	{
		printf("%s\t%p\t%p\n", list->command, list, list->next);
		list = list->next;
	}
	printf("\n");
	return 0;
}