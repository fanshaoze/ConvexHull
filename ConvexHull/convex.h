#pragma once
#include <stdio.h>

typedef struct 
{
	int x;
	int y;
}node;

int length = 4;
int range = 10;
void enumeration(node *nodes);
int judgein(node a, node b, node c, node d);
void printresult(node *nodes,int *mark);