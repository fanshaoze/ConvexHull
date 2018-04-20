#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "convex.h"
#include <time.h>
#include <math.h>
#include<string.h>

int partition(node *nodes, int left, int right)
{
	if (nodes == NULL)
		return -1;
	int pos = right;
	right--;
	while (left <= right)
	{
		while (left < pos && nodes[left].y <= nodes[pos].y)
			left++;
		while (right >= 0 && nodes[right].y > nodes[pos].y)
			right--;
		if (left >= right)
			break;
		swap(&nodes[left], &nodes[right]);
	}
	swap(&nodes[left], &nodes[pos]);
	return left;
}
int getMidIndex(node *nodes, int size)
{
	if (nodes == NULL || size <= 0)
		return -1;
	int left = 0;
	int right = size - 1;
	int midPos = right >> 1;
	int index = -1;
	while (index != midPos) {
		index = partition(nodes, left, right);
		if (index < midPos) {
			left = index + 1;
		}
		else if (index > midPos) {
			right = index - 1;
		}
		else {
			break;
		}
	}
	if (index == midPos) return -1;
	return index;
}

//int main()
//{
//	node* nodes = NULL;
//	generatenodes(nodes);
//	int index = getMidIndex(nodes, length);
//	printf("%d \n", index);
//	for (int i = 0; i<7; i++) {
//		printf("%d \n", nodes[i].y);
//	}
//	return 0;
//}
