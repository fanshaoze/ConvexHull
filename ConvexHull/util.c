#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "convex.h"
#include "malloc.h"
#include <time.h>

int generatenodes(node *nodes)
{
	int i, x = 0, y = 0;
	int *mark = (int*)calloc(length, sizeof(int));
	printf("length %d\n", length);
	srand((unsigned)time(NULL));
	for (i = 0; i < length; i++)
	{
		x = rand() % range + 1;
		y = rand() % range + 1;
		nodes[i].x = x;
		nodes[i].y = y;
		//printf("(%d %d)\n", x, y);
	}
	printresult(nodes, mark);
	return 0;
}
void printresult(node *nodes, int *mark) {
	int i = 0;
	for (i = 0; i < length; i++) {
		if (!mark[i]) {
			printf("node (%d %d)\n", nodes[i].x, nodes[i].y);
		}
	}
	return;
}