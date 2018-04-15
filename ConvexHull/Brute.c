#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "convex.h"
#include "malloc.h"
#include <time.h>


void enumeration(node *nodes) {
	int *mark = (int*)calloc(length, sizeof(int));
	int i, j, k, g;
	int isin;
	for (i = 0; i < length; i++) {
		for (j = 0; j < length; j++) {
			for (k = 0; k < length; k++) {
				for (g = 0; g < length; g++) {
					if (g != i &&g != j &&g != k && g != i &&
						i != j &&j != k &&i != k &&
						!mark[i] && !mark[j] && !mark[k]) {
						isin = judgein(nodes[i], nodes[j], nodes[k], nodes[g]);
					}
					else {
						continue;
					}
					if (isin == 1) {
						mark[g] = 1;
					}
					else {
						continue;
					}
				}
			}
		}
	}
	printresult(nodes, mark);
}
int side(node x, node y, node z)
{
	int a, b, c;
	a = y.y - x.y;
	b = x.x - y.x;
	c = x.x * y.y - x.y * y.x;
	return a * z.x + b * z.y - c;
}
int judgein(node a, node b, node c, node d) {
	int sameside0, sameside1, sameside2;
	sameside0 = side(a, b, d)*side(a, b, c);
	sameside1 = side(a, c, d)*side(a, c, b);
	sameside2 = side(b, c, d)*side(b, c, a);
	if (sameside0 >= 0 && sameside1 >= 0 && sameside2 >= 0)
	{
		return 1;
	}
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
		printf("(%d %d)\n", x, y);
	}
	//printresult(nodes, mark);
	return 0;
}