/* Musab Fiqi */

int alwaysTrue(void *data, void *helper) ;
void cleanup(struct Sim *s);
void close(struct Sim *s);
int compareFunc(void *data1, void *data2);
void disappear(struct Sim *s);
void fightBack(struct Sim *s);
int isInputNull(struct Sim *s, char *argv[]);
int isSaucerAtEdge(void *data, void *helper);
void move(struct Sim *s);
void pauseSim(struct Sim *s);
int secondElapsed(struct Sim *s);
int standingOverBase(void *data, void *helper);
void updatePoints(struct Alien *a);
void updateSim(struct Sim *s);
void victoryOrDefeat(struct Sim *s);
