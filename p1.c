#include <stdio.h>
#include <stdlib.h>

#include "typedef.h"
#include "linkedlist.h"

/* Musab Fiqi */

/* Prototype that demonstrates inserting strings into a linkedlist using a comparison function*/

/* Returns one*/
int func1(void *data1, void *data2){return 1;}

/* Main function */
int main()
{
	char *s = "Hello World!";
	char *t = "Goodbye World!";
	char *u = "Hello Again!";

	void* head = NULL;
	
	insert(&head,s,func1,1);
	insert(&head,t,func1,1);
	insert(&head,u,func1,1);

	return 0;
}
