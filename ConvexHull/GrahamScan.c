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

int cmp2(node nodes[], node p1, node p2) {
	int c1 = cross(nodes[0], p1, p2);  //tp,p1),c2=cross(p[0],tp,p2);  
	if (c1 == 0) {
		return dis(p1, nodes[0])<dis(p2, nodes[0]);
	}
	return c1>0;
}

int sort_place(node nodes[],int start) {
	int i, j;
	int *mark = (int*)calloc(length, sizeof(int));
	node temp;
	for (i = start; i < length-1; i++) {
		for (j = start; j < length -i-1; j++) {
			if ( nodes[j].x>nodes[j+1].x || ((nodes[j].x==nodes[j+1].x)&&nodes[j].y>nodes[j+1].y)) {
				temp = nodes[j+1];
				nodes[j+1] = nodes[j];
				nodes[j] = temp;
			}
		}
		//printresult(nodes, mark);
		//printf("\n");
	}
	return 0;
}
int sort_angle(node nodes[], int start) {
	int i, j;
	node temp;
	for (i = start; i < length; i++) {
		for (j = 0; j < length - i; j++) {
			if (!cmp2(nodes,nodes[j], nodes[j+1])) {
				temp = nodes[j+1];
				nodes[j+1] = nodes[j];
				nodes[j] = temp;
			}
		}
	}
	return 0;
}

node* graham_scan(node *nodes) {
	int i = 0;
	int *mark = (int*)calloc(length, sizeof(int));
	int top = 0;
	node *sort_nodes = (node*)calloc(length, sizeof(node));
	node *stack = (node*)calloc(length, sizeof(node));
	memcpy(sort_nodes, nodes, sizeof(node)*length);
	//printresult(nodes, mark);
	//printresult(sort_nodes, mark);
	top = 0;
	//sort_place(sort_nodes, 0);
	quicksort_place(sort_nodes, 0 ,length-1);
	printresult(sort_nodes, mark);
	printf("\n");
	sort_angle(sort_nodes, 1);
	stack[top++] = sort_nodes[0];

	stack[top++] = sort_nodes[1];
	
	//printresult(sort_nodes,mark);
	for (i = 2; i<length; i++) {
		if (cross(stack[top - 2], stack[top - 1], sort_nodes[i])>0) stack[top++] = sort_nodes[i];
		else {
			top--;
			while (top >= 2 && cross(stack[top - 2], stack[top - 1], sort_nodes[i]) <= 0) top--;
			stack[top++] = sort_nodes[i];
		}
	}
	for (i = top; i < length; i++) {
		mark[i] = 1;
	}
	//printresult(stack,mark);
	return stack;
}

void quicksort_place(node * nodes, int begin, int end)
{
	int i, j;
	if (begin < end) {
		i = begin + 1;  // 将array[begin]作为基准数，因此从array[begin+1]开始与基准数比较！  
		j = end;        // array[end]是数组的最后一位  
		while (i < j) {
			if (nodes[i].x > nodes[begin].x || ((nodes[i].x == nodes[begin].x) && nodes[i].y > nodes[begin].y)) { // 如果比较的数组元素大于基准数，则交换位置。  
				swap(&nodes[i], &nodes[j]);  // 交换两个数  
				j--;
			}
			else {
				i++;  // 将数组向后移一位，继续与基准数比较。  
			}
		}
		/* 跳出while循环后，i = j。
		* 此时数组被分割成两个部分  -->  array[begin+1] ~ array[i-1] < array[begin]
		*                           -->  array[i+1] ~ array[end] > array[begin]
		* 这个时候将数组array分成两个部分，再将array[i]与array[begin]进行比较，决定array[i]的位置。
		* 最后将array[i]与array[begin]交换，进行两个分割部分的排序！以此类推，直到最后i = j不满足条件就退出！
		*/
		if (nodes[i].x > nodes[begin].x || ((nodes[i].x == nodes[begin].x) && nodes[i].y >= nodes[begin].y)) {  // 这里必须要取等“>=”，否则数组元素由相同的值时，会出现错误！  
		
			i--;
		}

		swap(&nodes[begin], &nodes[i]);  // 交换array[i]与array[begin]  

		quicksort_place(nodes, begin, i);
		quicksort_place(nodes, j, end);
	}
}
void swap(node *a, node *b)
{
	int temp;
	temp = a->x;
	a->x = b->x;
	b->x = temp;

	temp = a->y;
	a->y = b->y;
	b->y = temp;
	return;
}