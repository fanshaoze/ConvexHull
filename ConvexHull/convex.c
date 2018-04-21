#include <stdio.h>
#include <stdlib.h>
#include "convex.h"
//#include "Brute.c"
//#include "GrahamScan.c"
#include "malloc.h"
#include <time.h>


int main() {
	length = 50000;
	range = 10;
	times = 1;
	for (int i = 0; i < times; i++) {
		node* nodes = (node*)calloc(length, sizeof(node));
		if (nodes == NULL) {
			return 1;
		}
		//	printf("length %d\n",sizeof(nodes));

		generatenodes(nodes);
		printf("brute--------------------------------------\n");
		//nodes[0].x = 1;
		//nodes[0].y = 1;
		//nodes[1].x = 2;
		//nodes[1].y = 2;
		//nodes[2].x = 3;
		//nodes[2].y = 3;
		//nodes[3].x = 4;
		//nodes[3].y = 4;
		//enumeration(nodes);

		printf("graham_scan--------------------------------------\n");
		graham_scan(nodes);
		divide_conquer(nodes, 0, length - 1);
		printf("what");
		free(nodes);
		return 0;
	}
	return 0;

}