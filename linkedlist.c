#include <stdio.h>
#include <stdlib.h>

#include "altmem.h"

#include "typedef.h"
#include "linkedlist.h"

/* Musab Fiqi */

/* struct node */
typedef struct Node{
	struct Node *next;
	void *data;
}Node;

/* Allocates Node */
static Node* allocateNode(void *DATA, int text)
{
	struct Node *ptr;
	static int count;
	
	ptr = alternative_malloc(sizeof(struct Node));

	if (ptr != NULL)
	{
		if (text) printf("DIAGNOSTIC: %d nodes allocated\n",++count);
		ptr->data = DATA;
	}
	else
	{
		if (text) printf("ERROR: linkedlist.c: Failed to malloc a Node\n");
	}

	return ptr;
}

/* Frees Node */
static void freeNode(struct Node *node, int text) 
{
	static int nodesFreed;
	alternative_free(node);
	if (text) printf("DIAGNOSTIC: %d nodes freed.\n",++nodesFreed);
}

/* Inserts node into the linkedlist */
int insert(void *p2head, void *data, ComparisonFunction goesInFrontOf, int text)
{
	struct Node **node = p2head;
	struct Node *newNode;
	static int count;
	
	newNode = allocateNode(data,text);
	while (*node != NULL && (goesInFrontOf((*node)->data,data)))
	{
		node = &((**node).next);
	}
	if (newNode != NULL)
	{
		newNode->next = *node;
		*node = newNode;
		return 1;
	}
	return 0;	
}

/* Deletes elements in the linked list that meet the mustGo criteria function */
int deleteSome(void *p2head, CriteriaFunction mustGo, void *helper, ActionFunction disposal, int text)
{
	struct Node **current = p2head;
	struct Node *holder;
	int nodesDeleted = 0;

	while(*current != NULL)
	{
		holder = *current;
		if (mustGo((*current)->data,helper))
		{
			*current = (**current).next;
			disposal(holder->data);
			freeNode(holder,text);
			nodesDeleted++;
		}
		else
		{
			current = &((**current).next);
		}
	}

	return nodesDeleted;
}

/* Iterates over linked list */
void iterate(void *head, ActionFunction doThis)
{
	struct Node *node = head;
	while (node != NULL)
	{
		doThis(node->data);
		node = node->next;
	}
}

/* If any element in the linkedlist is true for the CriteriaFunction, return true */
int any(void *head, CriteriaFunction yes, void *helper)
{
	struct Node *node = head;
	while (node != NULL)
	{
		if (yes(node->data,helper))
		{
			return 1;
		}
		node = node->next;
	}
	return 0;
}
