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
	int t = 0;
	for (int i = 0; i < divide_length; i++) {
		if (mark[i] != 1) t++;
	}
	node* ans = (node*)calloc(divide_length, sizeof(node));
	t = 0;
	for (int i = 0; i < divide_length; i++) {
		if (mark[i] != 1) {
			ans[t].x = nodes[i].x;
			ans[t].y = nodes[i].y;
			t++;
	}

	//memcpy(ans, nodes, divide_length * sizeof(node));
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
	for (int i = index-ql_length; i < index; i++) {
		central.x += ql[i].x;
		central.y += qr[i].y;
	}
	central.x = central.x / (double)ql_length;
	central.y = central.y / (double)ql_length;
	if (ql_length < 2) {
		central.x += 1;
		central.y += 1;
		//Ͷ��ȡ��
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
	min_y_index = begin + min_y_index;
	//node * gra_ans = (node*)calloc(divide_length, sizeof(node));
	memcpy(nodes, ql, ql_length* sizeof(node));
	memcpy(&nodes[index], qr, qr_length * sizeof(node));
	divide_quicksort(central, nodes, begin, end, min_y_index);
	return divide_graham_scan(nodes, divide_length,begin,end);
	

}

node* divide_graham_scan(node *nodes, int len,int begin,int end) {
	int i = 0;
	int top = 0;

	node *sort_nodes = (node*)calloc(len, sizeof(node));
	node *stack = (node*)calloc(len, sizeof(node));
	memcpy(sort_nodes, nodes, sizeof(node)*len);
	top = 0;
	printf("\n");
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
	int * mark2 = (int*)calloc(top, sizeof(int));
	for (i = begin+top; i <= end; i++) {
		mark[i] = 1;
	}
	memcpy(&nodes[begin], stack, top*sizeof(node));
	printresult(stack, mark2);
	free(mark2);
	return stack;
}


void divide_quicksort(node central, node * nodes, int begin, int end, int min_y_index)
{
	//swap(&nodes[t1], &nodes[min_y_index]);
	int i, j;
	if (begin<end) {
		i = begin + 1;
		j = end;
		while (i < j) {
			if (get_angle(central, nodes[min_y_index], nodes[i]) > get_angle(central, nodes[min_y_index], nodes[begin])) {
				swap(&nodes[i], &nodes[j]);
				j--;
			}
			else {
				i++;
			}
		}
		if (get_angle(central, nodes[min_y_index], nodes[i]) >= get_angle(central, nodes[min_y_index], nodes[begin])) {
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
