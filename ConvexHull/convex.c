#include <stdio.h>
#include <stdlib.h>
#include "convex.h"
//#include "Brute.c"
//#include "GrahamScan.c"
#include "malloc.h"
#include <time.h>


int main() {
	length = 50000;
	range = 100;
	times = 1;
	
	for (int i = 0; i < times; i++) {
		node* nodes = (node*)calloc(length, sizeof(node));
		if (nodes == NULL) {
			return 1;
		}
		//	printf("length %d\n",sizeof(nodes));
		printf("brute--------------------------------------");
		generatenodes(nodes);
		//enumeration(nodes);
		printf("graham_scan--------------------------------------");
		graham_scan(nodes);
		printf("what");
		free(nodes);
		
	}
	
	return 0;

}