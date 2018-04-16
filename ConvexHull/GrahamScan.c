#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "convex.h"
#include <time.h>
#include <math.h>
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

int sort_angle(node nodes[]) {

	return 0;
}
int sort_dis(node nodes[]) {

	return 0;
}