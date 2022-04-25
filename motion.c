#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "debug.h"

#include "framerate.h"
#include "motion.h"
#include "code.h"
#include "functions.h"

/* Musab Fiqi */

/* return 0 if y is less than or equal to zero, 
 * return 1 otherwise */
int onTheGround(void *data, void *helper)
{
	struct Alien *a = data;
	if(a->y <= 0 && TEXT) printf("Alien 0x%08X touches down at X = %f!\n",a->code,a->x);
	return a->y <= 0;
}

/*updates x value*/
void updateX(void *data)
{
	struct Alien *a = data;
	a->x = a->x + (a->vx * deltaT);
}

/*updates y value*/
void updateY(void *data)
{
	struct Alien *a = data;
	a->y = a->y + (a->vy * deltaT);
}

/* Reverses normal aliens only*/
void reverse(void *data)
{
	struct Alien *a = data;
	int type = codeToType(a->code);

	if (alienAtEdge(a->x,a->vx) && type != 3 && type !=4) 
	{ 
		a->vx = -a->vx;
		a->y = a->y - 3.0;
		if (TEXT) 
		{
			printf("Alien 0x%X drops to (%f, %f), VX to %+f at ET %f\n",a->code,a->x,a->y,a->vx,a->s->ET);
			printf("\n");
		}
	}
}

/* Is an alien at the edge*/
int alienAtEdge(double x, double vx)
{
	return (x <= -39.0 && vx < 0.0) || (x >= 39.0 && vx > 0.0);
}
