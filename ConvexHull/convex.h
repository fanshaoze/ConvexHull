#include <stdio.h>


typedef struct 
{
	int x;
	int y;
}node;

int length;
int range;
int times;

void enumeration(node *nodes);
int judgein(node a, node b, node c, node d);

int cross(node p0, node p1, node p2);
double dis(node a, node b);
int cmp2(node nodes[], node p1, node p2);
int cmp3(node nodes[], node p1, node p2, int equal);
int sort_place(node nodes[], int start);
int sort_angle(node nodes[], int start);
node* graham_scan(node *nodes);
void quicksort_place(node * nodes, int begin, int end);
void quicksort_angle(node * nodes, int begin, int end);

void swap(node *a, node *b);
void printresult(node *nodes, int *mark);
int generatenodes(node *nodes);
