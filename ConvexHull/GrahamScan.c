#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "convex.h"
#include <time.h>
#include <math.h>
#include<string.h>
int cross(node p0, node p1, node p2) {
	return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
}

double dis(node a, node b) {
	return sqrt(1.0*(a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

int cmp1(node p1, node p2) {
	return p1.x<p2.x || (p1.x == p2.x&&p1.y<p2.y);
}

int cmp2(node nodes[], node p1, node p2) {
	int c1 = cross(nodes[0], p1, p2);  //tp,p1),c2=cross(p[0],tp,p2);  
	if (c1 == 0) {
		return dis(p1, nodes[0])<dis(p2, nodes[0]);
	}
	return c1>0;
}

int sort_place(node nodes[],int start) {
	int i, j;
	node temp;
	for (i = start; i < length; i++) {
		for (j = 0; j < length - i; j++) {
			if (!cmp1(nodes[i], nodes[j])) {
				temp = nodes[j];
				nodes[j] = nodes[i];
				nodes[i] = temp;
			}
		}
	}
	return 0;
}
int sort_angle(node nodes[], int start) {
	int i, j;
	node temp;
	for (i = start; i < length; i++) {
		for (j = 0; j < length - i; j++) {
			if (!cmp1(nodes[i], nodes[j])) {
				temp = nodes[j];
				nodes[j] = nodes[i];
				nodes[i] = temp;
			}
		}
	}
	return 0;
}

node* graham_scan(node nodes[]) {
	int top = 0;
	node *sort_nodes = calloc(length, sizeof(node));
	node *stack = calloc(length, sizeof(node));
	memcpy(sort_nodes, nodes, length);
	top = 0;
	sort_place(sort_nodes, 0);
	sort_angle(sort_nodes, 1);
	stack[top++] = sort_nodes[0];
	stack[top++] = sort_nodes[1];
	for (int i = 2; i<length; i++) {
		if (cross(stack[top - 2], stack[top - 1], sort_nodes[i])>0) stack[top++] = sort_nodes[i];
		else {
			top--;
			while (top >= 2 && cross(stack[top - 2], stack[top - 1], sort_nodes[i]) <= 0) top--;
			stack[top++] = sort_nodes[i];
		}
	}
	stack[top++] = sort_nodes[0];
	return stack;
}