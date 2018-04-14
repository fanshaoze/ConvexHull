#pragma once
#include <stdio.h>

typedef struct 
{
	int x;
	int y;
}node;

void enumeration(node *nodes);
int judgein(node a, node b, node c, node d);
void printresult(node *nodes,int *mark);