#include <stdio.h>
#include "code.h"

/* Musab Fiqi */

/*THE DEBUG MESSAGES FOR THESE FUNCTIONS ARE IN OUTPUT.C
 *THIS IS BECAUSE THEY WOULD'VE RETURNED THE SAME VALUES EVERY TIME*/

/*return the color of the alien*/
int codeToColor (unsigned int code)
{
	code = code << 25;
	code = code >> 25;
	code = code >> 4;
	return (int) code;
}

/*returns the type of the alien*/
int codeToType (unsigned int code)
{
	code = code << 17;
	code = code >> 17;
	code = code >> 12;
	return (int) code;
}

/*return the point value of the alien*/
int codeToPoints (unsigned int code)
{
	code = code << 3;
	code = code >> 3;
	code = code >> 20;
	return (int) code;
}
