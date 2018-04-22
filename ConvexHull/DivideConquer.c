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
		while (left < pos && nodes[left].x <= nodes[pos].x)
			left++;
		while (right >= 0 && nodes[right].x > nodes[pos].x)
			right--;
		if (left >= right)
			break;
		swap(&nodes[left], &nodes[right]);
	}
	swap(&nodes[left], &nodes[pos]);
	return left;
}
int getMidIndex(node *nodes, int begin,int end)
{
	int size = end - begin + 1;
	printf("begin:%d,end:%d,size:%d\n", begin, end, size);
	if (nodes == NULL || size <= 0)
		return -1;
	int left = begin;
	int right = end;
	int midPos = (right + left)/ 2;
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
	return index;
}

node* divide_conquer(node* nodes, int begin, int end) {
	int divide_length = end - begin + 1;
	if (divide_length <= 3) return nodes;
	//node* ans = (node*)calloc(divide_length, sizeof(node));
	//memcpy(ans, nodes, divide_length * sizeof(node));
	int *mark = (int*)calloc((divide_length), sizeof(int));
	printf("nodes begin %d,end %d \n",begin,end);
	divide_printresult(nodes, mark,begin,end);

	int index = getMidIndex(nodes, begin,end);

	printf("index %d \n", index);
	divide_printresult(nodes, mark, begin, end);
	int ql_length = index - begin;
	int qr_length = end - index + 1;

	node* ql = (node*)calloc(ql_length, sizeof(node));
	printf("qllen:%d,qrlen:%d\n", ql_length, qr_length);
	memcpy(ql, divide_conquer(nodes, begin, index - 1), ql_length * sizeof(node));
	node* qr = (node*)calloc(qr_length, sizeof(node));
	memcpy(qr, divide_conquer(nodes, index, end), qr_length*sizeof(node));

	node central;
	central.x = 0;
	central.y = 0;
	for (int i = 0; i < index; i++) {
		central.x += ql[i].x;
		central.y += qr[i].y;
	}
	central.x = central.x / (double)ql_length;
	central.y = central.y / (double)ql_length;
	if (ql_length < 2) {
		central.x += 1;
		central.y += 1;
		//Í¶»úÈ¡ÇÉ
	}
	printf("central x:%lf y:%lf ", central.x, central.y);
	double min_y = ql[0].y;
	int min_y_index = 0;
	for (int i = 1; i < ql_length; i++) {
		if (ql[i].y < min_y) {
			min_y = ql[i].y;
			min_y_index = i;
		}
	}
	node * gra_ans = (node*)calloc(divide_length, sizeof(node));
	memcpy(gra_ans, ql, ql_length* sizeof(node));
	memcpy(gra_ans, qr, qr_length * sizeof(node));
	divide_quicksort(central, gra_ans, begin, end, min_y_index);
	divide_graham_scan(gra_ans, divide_length);
	return gra_ans;

}

node* divide_graham_scan(node *nodes, int len) {
	int i = 0;
	int *mark = (int*)calloc(len, sizeof(int));
	int top = 0;
	node *sort_nodes = (node*)calloc(len, sizeof(node));
	node *stack = (node*)calloc(len, sizeof(node));
	memcpy(sort_nodes, nodes, sizeof(node)*len);
	//printresult(nodes, mark);
	//printresult(sort_nodes, mark);
	top = 0;
	//sort_place(sort_nodes, 0);
	//printresult(sort_nodes, mark);
	printf("\n");
	//sort_angle(sort_nodes, 1);
	//printresult(sort_nodes, mark);
	//printf("\n");
	//printresult(sort_nodes, mark);
	stack[top++] = sort_nodes[0];

	stack[top++] = sort_nodes[1];

	//printresult(sort_nodes,mark);
	for (i = 2; i < len; i++) {
		if (cross(stack[top - 2], stack[top - 1], sort_nodes[i]) > 0) stack[top++] = sort_nodes[i];
		else {
			top--;
			while (top >= 2 && cross(stack[top - 2], stack[top - 1], sort_nodes[i]) <= 0) top--;
			stack[top++] = sort_nodes[i];
		}
	}
	for (i = top; i < len; i++) {
		mark[i] = 1;
	}
	printresult(stack, mark);
	return stack;
}


void divide_quicksort(node central, node * nodes, int begin, int end, int min_y_index)
{
	swap(&nodes[0], &nodes[min_y_index]);
	int i, j;
	if (begin < end) {
		i = begin + 1;
		j = end;
		while (i < j) {
			if (get_angle(central, nodes[0], nodes[i]) > get_angle(central, nodes[0], nodes[begin])) {
				swap(&nodes[i], &nodes[j]);
				j--;
			}
			else {
				i++;
			}
		}
		if (get_angle(central, nodes[0], nodes[i]) >= get_angle(central, nodes[0], nodes[begin])) {
			i--;
		}

		swap(&nodes[begin], &nodes[i]);
		quicksort_place(nodes, begin, i);
		quicksort_place(nodes, j, end);
	}
}

double get_angle(node central, node a, node b) {
	double angle = 0;
	double v0_x = a.x - central.x;
	double v0_y = a.y - central.y;

	double v1_x = b.x - central.x;
	double v1_y = b.y - central.y;
	double cos = (v0_x*v1_x + v0_y*v1_y) / (sqrt(v0_x*v0_x + v0_y*v0_y)*sqrt(v1_x*v1_x + v1_y*v1_y));
	angle = acos(cos);
	return angle;

}


//int main()
//{
//	length = 10;
//	range = 10;
//	node* nodes_v = calloc(length, sizeof(node));
//	generatenodes(nodes_v);
//	int index = getMidIndex(nodes_v, length);
//	printf("%d \n", index);
//	for (int i = 0; i < length; i++) {
//		printf("%d %d \n", i, nodes_v[i].x);
//	}
//	return 0;
//}
