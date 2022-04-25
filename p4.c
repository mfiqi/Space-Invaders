#include <stdio.h>
#include <stdlib.h>

#include "typedef.h"
#include "linkedlist.h"

/* Musab Fiqi */

/* Prototype that shows any function is working*/

/* Comparison Function */
int func1(void *data1, void *data2){return 0;}

/* Criteria Function */
int func3(void *data, void *helper) {return 1;}

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
	
	if (any(head,func3,NULL)) printf("any is working!\n");
	
	return 0;
}
