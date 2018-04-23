#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "convex.h"
#include "malloc.h"
#include <time.h>

int generatenodes(node *nodes)
{
	int i; 
	double x = 0.0, y = 0.0;
	int *mark = (int*)calloc(length, sizeof(int));
	printf("length %d\n", length);
	srand((unsigned)time(NULL));
	for (i = 0; i < length; i++)
	{
		x = rand() / (double)(RAND_MAX / range);
		y = rand() / (double)(RAND_MAX / range);
		//x = (rand() / range)*range;
		//y = (rand() / range)*range;
		while (x == 0.0||y == 0.0)
		{
			x = rand() / (double)(RAND_MAX / range);
			y = rand() / (double)(RAND_MAX / range);
		}
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
			printf("node (%lf %lf)\n", nodes[i].x, nodes[i].y);
		}
	}
	return;
}

void divide_printresult(nodearray pnode) {
	for (int i = 0; i <= pnode.length; i++) {
		if (!mark[i]) {
			printf("node (%lf %lf)\n", pnode.nodes[i].x, pnode.nodes[i].y);
		}
	}
	return;
}

void swap(node *a, node *b)
{
	double temp;
	temp = a->x;
	a->x = b->x;
	b->x = temp;

	temp = a->y;
	a->y = b->y;
	b->y = temp;
	return;
}

double cross(node p0, node p1, node p2) {
	return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
}