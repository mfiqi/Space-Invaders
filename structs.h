/* Musab Fiqi */

/* Sim Struct */
struct Sim
{
	double ET, base;
	int points;
	void *head;
	FILE *input, *output;
	char c;
};

/* Alien Struct */
struct Alien
{
	unsigned int code;
	double x,y,vx,vy;
	struct Sim *s;
};
