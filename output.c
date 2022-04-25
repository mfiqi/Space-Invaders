#include <stdio.h>
#include <math.h>

#include "invaders.h"
#include "typedef.h"
#include "linkedlist.h"

#include "structs.h"
#include "debug.h"
#include "framerate.h"

#include "output.h"
#include "code.h"
#include "motion.h"
#include "lab4.h"
#include "memory.h"
#include "functions.h"

/* Musab Fiqi */

/* Master output prints alien depending on debug.h */
void masterOutput(struct Sim *s)
{
	if(GRAPHICS) printAlienGraphics(s);
	if((TEXT && secondElapsed(s)) || DEBUG) printAlienText(s);	
}

/* Prints the return value of scanf */
void endOfFile(int items)
{
	if(TEXT) printf("Input terminated: scanf returned %d\n\n",items);
}

/* Prints alien graphics */
void printAlienGraphics(struct Sim *s)
{
	sa_clear();
	sa_base(s->base);
	iterate(s->head, draw_alien);
	if(s->c == ' ') sa_bolt(s->base);
	sa_time(1000.0 * s->ET);
	sa_score(s->points);
	sa_refresh();
	microsleep(deltaT * 1000000);
}

/* Draws alien */
void draw_alien(void *data)
{
	struct Alien *a = data;
	if(a->y < 0.0) a->y = 0.0;
	sa_alien(codeToType(a->code),codeToColor(a->code),a->x,a->y);
}

/* Prints alien text */
void printAlienText(struct Sim *s)
{
	printf("\nCode       T C Pts ( __X______, __Y______) ( __VX_____, __VY_____) ET= %f\n",s->ET);
	iterate(s->head,printAlien);
	printf("\n");
}

/* Prints second boundary debug message */
void crossesSecondBoundary(struct Sim *s)
{
	if(DEBUG) printf("\ncrosses_second_boundary: Cur = %d, Prev = %d, ET = %f: returning %d\n",(int) s->ET, (int) (s->ET - deltaT), s->ET, (int) s->ET == s->ET);
}

/* Prints alien */
void printAlien(void *data)
{
	struct Alien *a = data;
	printf("0x%08X %d %d %3d (%10f,%10f) (%10f,%10f)\n",a->code,codeToType(a->code),codeToColor(a->code),codeToPoints(a->code),a->x,a->y,a->vx,a->vy,a->s->ET);
}

/* Prints debug messages */
void resultsFromCode(unsigned int code)
{
	printf("color_from_code: isolating 3 bits after shifting 4 on %08X gives %d\n",code,codeToColor(code));
	printf("type_from_code: isolating 3 bits after shifting 12 on %08X gives %d\n",code,codeToType(code));
	printf("points_from_code: isolating 9 bits after shifting 20 on %08X gives %d\n",code,codeToPoints(code));
}
