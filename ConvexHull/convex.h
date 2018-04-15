#include <stdio.h>


typedef struct 
{
	int x;
	int y;
}node;

int length;
int range;

void enumeration(node *nodes);
int judgein(node a, node b, node c, node d);
void printresult(node *nodes,int *mark);

int cross(node p0, node p1, node p2);
double dis(node a, node b);
int cmp1(node p1, node p2);
int cmp2(node nodes[], node p1, node p2);

