#include <stdio.h>
#include <stdlib.h>

#include "altmem.h"
#include "structs.h"

#include "debug.h"
#include "memory.h"

/* Musab Fiqi */

/* Allocates Dynamic Memory:
 *
 * Calls Malloc or Calloc to dynamically allocate memory
 * for alien structure
 *
 * Returns the pointer value it got from Malloc*/
struct Alien *allocateMemory()
{
	/*counts number of successful allocations*/
	static int count;
	struct Alien *ptr;
	
	/*print number of allocated aliens if success, else print ERROR*/
	ptr = alternative_malloc(sizeof(struct Alien));

	if (ptr != NULL) {
		count++;
		if(TEXT) printf("allocate_alien: %d allocated\n",count);
	}
	else
	{
		if(TEXT) printf("ERROR: allocate_alien: failed to allocate\n");
	}
	return ptr;
}

/*Function that frees memory*/
void freeAlien(void *data){
	static int count;
	struct Alien *a = data;
	if (TEXT) printf("free_alien: %d freed\n",++count);
	alternative_free(data);
}
