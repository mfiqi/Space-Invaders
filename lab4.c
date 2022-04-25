#include <stdio.h>
#include <stdlib.h>

#include "invaders.h"
#include "typedef.h"
#include "linkedlist.h"

#include "debug.h"
#include "framerate.h"
#include "structs.h"

#include "lab4.h"
#include "output.h"
#include "memory.h"
#include "functions.h"
#include "motion.h"
#include "code.h"

/* Musab Fiqi */

/* Starts the program */
int main(int argc, char *argv[])
{
	double starts = now();
	double time;
	struct Sim world={0.0,0.0,0,NULL,NULL,NULL};

	if (masterInit(&world,argc,argv))
	{
		input(&world);
		simLoop(&world);
		masterTeardown(&world,argv);
	}
	else
	{
		printf("ERROR: FAILED TO INITIALIZE\n");
	}
	time = now() - starts;
	printf("Total run time is %.9f seconds.\n",time);
	return 0;
}

/* Master Teardown */
void masterTeardown(struct Sim *s, char *argv[])
{
	if(GRAPHICS) sa_teardown();
	printf("DIAGNOSTIC: Closed input file %s.\n",argv[1]);
	fclose(s->input);
}

/* Master init */
int masterInit(struct Sim *s, int argc, char *argv[])
{
	/*Deal with command line paramters*/
	if (argc > 1)
	{
		s->input = fopen(argv[1],"r");
		if (isInputNull(s,argv))
		{
			return 0;	
		}
	}
	else
	{
		printf("ERROR: No input file given on command line.\n");
		return 0;
	}
	if(TEXT || (GRAPHICS && sa_initialize()))
	{
		return 1;
	}
	else
	{
		close(s);
		return 0;
	}
}

/* Inputs Aliens, handles errors, then passes them to simLoop */
void input(struct Sim *s)
{
	int items;
	struct Alien a;
	struct Alien *ptr;
	
	/* If scanf successfully reads, it will use that data to copy to a dynamically allocated structure
	 * Hands off a pointer to the statically allocated alien
	 * Then copies it to dynamic memory and puts it on the list*/
	a.s = s;
	while(5 == (items = fscanf(s->input,"%X %lf %lf %lf %lf",&a.code,&a.x,&a.y,&a.vx,&a.vy)))
	{
		if((ptr = allocateMemory()) != NULL)
		{
			if(DEBUG) resultsFromCode(a.code);
			*ptr = a;	
			if(!insert(&s->head,ptr,compareFunc,TEXT))
			{
				freeAlien(ptr);
			}
			else
			{
				if(DEBUG) printf("add_new_alien: inserted code %X\n",a.code);
			}
		}
	}
	endOfFile(items);
}

/* Simulation Loop */
void simLoop(struct Sim *s) 
{
	/* while we haven't lost and aliens still exist, fight on! */
	while(!any(s->head,onTheGround,NULL) && s->head)
	{
		masterOutput(s);
		updateSim(s);
		fightBack(s);
		disappear(s);
		move(s);
	}
	if (GRAPHICS) pauseSim(s);
	if (TEXT) 
	{
		if(s->head) printAlienText(s);	
		victoryOrDefeat(s);
	}
	cleanup(s);
}
