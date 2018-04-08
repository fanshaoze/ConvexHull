#include <stdio.h>
#include "convex.h"


//node nodes[10];
void enumeration(node *nodes) {
	int i, j, k, g;
	int isin;
	int length = sizeof(nodes) / sizeof(nodes[0]);
	for (i = 0; i < length; i++) {
		for (j = 0; j < length; j++) {
			for (k = 0; k < length; k++) {
				for (g = 0; g < length; g++) {
					isin = judgein(nodes[i], nodes[j], nodes[k], nodes[g]);
				}
			}
		}
	}
}
int judgein(node a, node b, node c, node d) {
	return 0;
}
int main() {
	int i = 10;
	node *nodes;
	nodes = (node*)malloc(i * sizeof(node));
	printf("what");
	return 0;

}