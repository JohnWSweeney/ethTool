#pragma once
#include <stdio.h>
#include <stdlib.h>

struct node
{
	char command[123];
	struct node* next;
};

int init(struct node** list, char* command);
int addBack(struct node** list, char* command);
int clear(struct node** list);
int isEmpty(struct node* list);
int print(struct node* list);