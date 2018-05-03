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
int getMidIndex(nodearray pnode)
{
	int size = pnode.length;
	//printf("size:%d\n", size);
	if (pnode.nodes == NULL || size <= 0)
		return -1;
	int left = 0;
	int right = size-1;
	int midPos = (right + left)/ 2;
	int index = -1;
	while (index != midPos) {
		index = partition(pnode.nodes, left, right);
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

nodearray divide_conquer(nodearray pnode) {
	//printf("begin\n");
	int divide_length = pnode.length;
	if (divide_length <= 3) return pnode;
	int t = 0;
//	for (int i = 0; i < divide_length; i++) {
//		if (mark[i] != 1) t++;
//	}
	//node* ans = (node*)calloc(divide_length, sizeof(node));
	//t = 0;
	//for (int i = 0; i < divide_length; i++) {
	//	if (mark[i] != 1) {
	//		ans[t].x = pnode.nodes[i].x;
	//		ans[t].y = pnode.nodes[i].y;
	//		t++;
	//}

	//memcpy(ans, nodes, divide_length * sizeof(node));
	//printf("nodes begin %d,end %d \n",begin,end);
	//divide_printresult(pnode);

	int index = getMidIndex(pnode);
	//divide_printresult(pnode);
	nodearray pl,pr;
	pl.nodes = &t;
	pr.nodes = &t;
	init(&pl, index);
	init(&pr, divide_length-index);
	//printf("index %d \n", index);
	node* p = pnode.nodes;
	p = p + index;
	memcpy(pl.nodes, pnode.nodes, index * sizeof(node));
	memcpy(pr.nodes,p, (divide_length - index) * sizeof(node));
	//memcpy(pr.nodes, &(pnode.nodes[index]), (divide_length - index) * sizeof(node));
	//printf("pl \n");
	//divide_printresult(pl);
	//printf("pr \n");
	//divide_printresult(pr);
	nodearray ql, qr;
	ql.nodes = &t;
	qr.nodes = &t;
	ql.length = 0;
	qr.length = 0;

	nodearray temp;
	temp.nodes = &t;
	temp.length = 0;
	init(&temp, temp.length);
	temp = divide_conquer(pl);

	init(&ql, temp.length);
	memcpy(ql.nodes, temp.nodes, ql.length * sizeof(node));
	temp = divide_conquer(pr);

	init(&qr, temp.length);
	memcpy(qr.nodes, temp.nodes, qr.length * sizeof(node));
	//printf("qllen:%d,qrlen:%d\n", ql.length, qr.length);
	
	node central;
	central.x = 0;
	central.y = 0;
	for (int i = 0; i < ql.length; i++) {
		central.x += ql.nodes[i].x;
		central.y += qr.nodes[i].y;
	}
	central.x = central.x / (double)ql.length;
	central.y = central.y / (double)ql.length;
	if (ql.length < 2) {
		central.x -= 0.0001;
		central.y += 0.1;
		//Í¶»úÈ¡ÇÉ
	}
	//printf("central x:%lf y:%lf \n", central.x, central.y);
	double min_y = ql.nodes[0].y;
	int min_y_index = 0;
	for (int i = 1; i < ql.length; i++) {
		if (ql.nodes[i].y < min_y) {
			min_y = ql.nodes[i].y;
			min_y_index = i;
		}
	}
	//printf("min_y_index x:%lf y:%lf \n", ql.nodes[min_y_index].x, ql.nodes[min_y_index].y);
	//min_y_index = begin + min_y_index;
	//node * gra_ans = (node*)calloc(divide_length, sizeof(node));
	node min_node = ql.nodes[min_y_index];
	nodearray result;
	result.nodes = &t;
	result.length = ql.length + qr.length;
	init(&result, ql.length+qr.length);
	p = result.nodes;
	p += ql.length;
	memcpy(result.nodes, ql.nodes, ql.length* sizeof(node));
	memcpy(p, qr.nodes, qr.length * sizeof(node));
	//divide_printresult(result);
	int relen = result.length;
	int part = 0;
	result = upordown(central,result,min_y_index);
	part = result.length;
	result.length = relen;
	//printf("changed result part:%d \n", part);
	//divide_printresult(result);
	nodearray ml, mr;
	ml.nodes = &t;
	mr.nodes = &t;
	ml.length = part;
	mr.length = result.length-part;
	init(&ml, part);
	p = result.nodes;
	p += part;
	memcpy(ml.nodes, result.nodes, ml.length * sizeof(node));
	init(&mr, mr.length);
	memcpy(mr.nodes,p , mr.length * sizeof(node));
	//printf(" lr:\n");
	//divide_printresult(ml);
	//printf(" mr:\n");
	//divide_printresult(mr);
	divide_quicksort(central,ml.nodes, 0,ml.length-1,min_node);
	divide_quicksort(central, mr.nodes, 0, mr.length - 1, min_node);
	node tempnode;

	for (int i = 0; i < mr.length/2; i++) {
		swap(mr.nodes + i, mr.nodes + mr.length - 1 - i);
		//tempnode.x = mr.nodes[i].;
		//tempnode.y = mr.nodes[i].y;
		//mr.nodes[i].x = mr.nodes[mr.length -1 - i].x;
		//mr.nodes[i].y = mr.nodes[mr.length - 1 - i].y;
		//mr.nodes[mr.length - 1 - i].x = tempnode.x;
		//mr.nodes[mr.length - 1 - i].y = tempnode.y;
	}
	//printf("changed mr\n");
	//divide_printresult(mr);
	p = result.nodes;
	p += ml.length;
	memcpy(result.nodes, ml.nodes, ml.length * sizeof(node));
	memcpy(p, mr.nodes, mr.length * sizeof(node));
	return divide_graham_scan(result);
	printf(result.length);
	//return pnode;

}

nodearray upordown(node central,nodearray result,int min_y_index) {
	nodearray ql, qr;
	int t = 0;
	int i = 0;
	int m = 0, n = 0;
	ql.nodes = &t;
	qr.nodes = &t;
	ql.length = 0;
	qr.length = 0;
	init(&ql, result.length);
	init(&qr, result.length);
	for (i = 0; i < result.length; i++) {
		if (!cross(central, result.nodes[min_y_index],result.nodes[i])){
			ql.nodes[m].x = result.nodes[i].x;
			ql.nodes[m].y = result.nodes[i].y;
			m++;
		}
		else
		{
			qr.nodes[n].x = result.nodes[i].x;
			qr.nodes[n].y = result.nodes[i].y;
			n++;
		}
	}
	ql.length = m;
	qr.length = n;
	node* p = result.nodes;
	p += ql.length;
	memcpy(result.nodes, ql.nodes, ql.length * sizeof(node));
	memcpy(p, qr.nodes, qr.length * sizeof(node));
	result.length = ql.length;
	return result;
}

nodearray divide_graham_scan(nodearray pnode) {
	//printf("graham_scan\n");
	int i = 0;
	int top = 0;
	int len = pnode.length;
	node *sort_nodes = (node*)calloc(len, sizeof(node));
	node *stack = (node*)calloc(len, sizeof(node));
	memcpy(sort_nodes, pnode.nodes, sizeof(node)*len);
	top = 0;
	//printf("\n");
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
	//int * mark2 = (int*)calloc(top, sizeof(int));
	nodearray result;
	int t = 0;
	result.nodes = &t;
	init(&result, top);

	memcpy(result.nodes, stack, top*sizeof(node));
	//printf("result\n");
	//divide_printresult(result);
	//printresult(stack, mark2);
	return result;
}

void divide_quicksort(node central, node* nodes, int begin,int end,node min_y)
{
	int i, j;
	if (begin<end) {
		i = begin + 1;
		j = end;
		while (i < j) {
			if (get_angle(central, min_y, nodes[i]) > get_angle(central, min_y, nodes[begin])) {
				swap(&nodes[i], &nodes[j]);
				j--;
			}
			else {
				i++;
			}
		}
		if (get_angle(central, min_y, nodes[i]) >= get_angle(central, min_y, nodes[begin])) {
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
