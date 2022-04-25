#include <stdio.h>
#include <stdlib.h>

#include "typedef.h"
#include "linkedlist.h"

/* Musab Fiqi */

/* Prototype that iterates linked list and uses an action function*/

/* Comparison Function */
int func1(void *data1, void *data2){return 0;}

/* Action Function */
void func2(void *data)
{
	char *str = data;
	printf("%s\n",str);
}

/* Main Function */
int main()
{
	char *s = "Hello World!";
	char *t = "Goodbye World!";
	char *u = "Hello Again!";

	void *head = NULL;

	insert(&head,s,func1,1);
	insert(&head,t,func1,1);
	insert(&head,u,func1,1);
	
	iterate(head,func2);
	
	return 0;
}
