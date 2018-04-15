#include <stdio.h>
#include <stdlib.h>
#include "convex.h"
//#include "Brute.c"
//#include "GrahamScan.c"
#include "malloc.h"
#include <time.h>


int main() {
	length = 4;
	range = 10;
	node* nodes = (node*)malloc(length * sizeof(node));
	if (nodes == NULL) {
		return 1;
	}
//	printf("length %d\n",sizeof(nodes));

	generatenodes(nodes);
	enumeration(nodes);
	printf("what");
	free(nodes);
	return 0;

}