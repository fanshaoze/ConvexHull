#include <stdio.h>
#include <stdlib.h>
#include "convex.h"
//#include "Brute.c"
//#include "GrahamScan.c"
#include "malloc.h"
#include <time.h>
#include <string.h>


int main() {
	length =10;
	range = 100.0;
	times = 1;
	clock_t d1 = 0, d2 = 0, d3 = 0;
	mark = (int*)calloc((length), sizeof(int));
	node* nodes = (node*)calloc(length, sizeof(node));
	if (nodes == NULL) {
		return 1;
	}
	for (int i = 0; i < times; i++) {
		
		//	printf("length %d\n",sizeof(nodes));
		
		generatenodes(nodes);
		printf("brute--------------------------------------\n");
		clock_t start1,start2,start3, stop1,stop2,stop3;
		//printf("Use Time:%ld\n", (stop - start));
		start1 = clock();
		enumeration(nodes);
		stop1 = clock();
		printf(" brute Use Time:%ld\n", (stop1 - start1));
		d1 += stop1 - start1;
		int t = 0;
		mark = (int*)calloc((length), sizeof(int));
		printf("graham_scan--------------------------------------\n");
		start2 = clock();
		graham_scan(nodes);
		stop2 = clock();
		printf(" graham Use Time:%ld\n", (stop2 - start2));
		d2 += stop2 - start2;
		mark = (int*)calloc((length), sizeof(int));
		nodearray pnode;
		pnode.nodes = &t;
		pnode.length = length;
		//pnode.length = len;
		pnode.nodes = (node*)calloc(pnode.length, sizeof(node));
		//init(pnode, length);
		memcpy(pnode.nodes,nodes,length*sizeof(node));
		nodearray temp;
		printf("divide--------------------------------------\n");
		start3 = clock();
		temp = divide_conquer(pnode);
		divide_printresult(temp);
		stop3 = clock();
		d3 += stop3 - start3;
		//printf(" divide Use Time:%f\n", (double)(stop3 - start3) / CLOCKS_PER_SEC);
		printf(" divide Use Time:%ld\n", (stop3 - start3));
		printf("length:%d\n", temp.length);
		printf("what");
		//free(nodes);
		nodes = (node*)calloc(length, sizeof(node));
		if (nodes == NULL) {
			return 1;
		}
		//return 0;
	}
	printf("%ld,%ld,%ld", d1, d2, d3);
	return 0;

}