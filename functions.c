#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "invaders.h"
#include "typedef.h"
#include "linkedlist.h"

#include "structs.h"
#include "debug.h"
#include "framerate.h"

#include "motion.h"
#include "functions.h"
#include "code.h"
#include "memory.h"
#include "output.h"

/* Musab Fiqi */

void close(struct Sim *s)
{
	fclose(s->input);
	printf("ERROR: Graphics failed to initialized.\n");
}

/* Compares which alien has the greater y value*/
int compareFunc(void *data1, void *data2)
{
	struct Alien *a1 = data1;
	struct Alien *a2 = data2;
	return (a1->y) > (a2->y);
}

/* Are we standing over base */
int standingOverBase(void *data, void *helper)
{
	struct Alien *a = data;
	
	if ((int)a->x == (int)a->s->base) 
	{
		updatePoints(a);
		return 1;
	}
	return 0;
}

/* Checks if a second has elapsed */
int secondElapsed(struct Sim *s)
{
	if (DEBUG) crossesSecondBoundary(s);
	return (!(s->ET - floor(s->ET)));
}

/* Runs once a second, deletes aliens over base */
void fightBack(struct Sim *s)
{
	if (s->c == ' ')
	{
		crossesSecondBoundary(s);
		deleteSome(&s->head,standingOverBase,NULL,freeAlien,TEXT);
	}
}

/* Update points */
void updatePoints(struct Alien *a)
{
	a->s->points = a->s->points + codeToPoints(a->code);
	if(TEXT) printf("Bolt hits alien at (%f,%f), scores %d points!\n",a->x,a->y,codeToPoints(a->code));
	if(GRAPHICS) sa_status("Bolt hits an alien!\n");
}


/* Pause Sim */
void pauseSim(struct Sim *s)
{
	double time = 0;
	while(time < 4.0)
	{
		time = time + deltaT;
		printAlienGraphics(s);
	}
}

/* Disappears Saucer */
void disappear(struct Sim *s)
{
	deleteSome(&s->head,isSaucerAtEdge,NULL,freeAlien,TEXT);
}

/* Checks if saucer is at edge, If so, prints appropriate messages */
int isSaucerAtEdge(void *data, void *helper)
{
	struct Alien *a = data;
	int type = codeToType(a->code);
	if ((type == 3 || type == 4) && alienAtEdge(a->x,a->vx))
	{
		if(TEXT) printf("Flying saucer worth %d points escapes at ET = %f!\n",codeToPoints(a->code),a->s->ET);
		if(GRAPHICS) sa_status("Flying saucer escapes!\n");
		return 1;
	}
	return 0;
}

/* Updates x, vx, y, and ET */
void updateSim(struct Sim *s)
{
	s->ET = s->ET + deltaT;
	s->c = sa_getch();
	iterate(s->head,updateX);
	iterate(s->head,updateY);
	iterate(s->head,reverse);
}

void move(struct Sim *s)
{
	if (s->c == 'a' && s->base > -38) s->base = s->base -1;
	if (s->c == 'd' && s->base < 38) s->base = s->base +1;
}

/* Removes all aliens from linked list */
void cleanup(struct Sim *s)
{
	int aliensDeleted = 0;

	if(TEXT) printf("Clearing the attacking list...\n");
	aliensDeleted = deleteSome(&s->head,alwaysTrue,NULL,freeAlien,TEXT);
	if(TEXT) printf("    ... %d cleared\n",aliensDeleted);
}

/* prints victory or defeat */
void victoryOrDefeat(struct Sim *s)
{
	if (!s->head)
	{
		printf("\nVictory! No attackers remain at ET = %f\n",s->ET);
	}
	else
	{
		printf("\nDefeat! Aliens land at ET = %f\n",s->ET);
	}
	printf("Total score is %d points\n",s->points);
}

/* Checks if file input is null */
int isInputNull(struct Sim *s, char *argv[])
{
	if (s->input == NULL)
	{
		printf("ERROR: unable to open %s for input.\n",argv[1]);
		fclose(s->input);
		return 1;
	}
	else
	{
		printf("DIAGNOSTIC: Successfully opened %s for input.\n",argv[1]);
		return 0;
	}
}

/* Returns 1 */
int alwaysTrue(void *data, void *helper) {return 1;}
