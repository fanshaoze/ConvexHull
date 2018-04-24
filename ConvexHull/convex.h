#include <stdio.h>


typedef struct 
{
	double x;
	double y;
}node;

typedef struct
{
	node* nodes;
	int length;
}nodearray;

int length;
double range;
int times;
int *mark;

void enumeration(node *nodes);
int judgein(node a, node b, node c, node d);


double dis(node a, node b);
int cmp2(node nodes[], node p1, node p2);
int cmp3(node nodes[], node p1, node p2, int equal);
int sort_place(node nodes[], int start);
int sort_angle(node nodes[], int start);
node* graham_scan(node *nodes);
void quicksort_place(node * nodes, int begin, int end);
void quicksort_angle(node * nodes, int begin, int end);

int partition(node *nodes, int left, int right);
int getMidIndex(nodearray pnode);
nodearray divide_conquer(nodearray pnode);
nodearray divide_graham_scan(nodearray pnode);
void divide_quicksort(node central, node * nodes, int begin, int end, node min_y);
double get_angle(node central, node a, node b);
nodearray upordown(node central, nodearray result, int min_y_index);

void swap(node *a, node *b);
void printresult(node *nodes, int *mark);
int generatenodes(node *nodes);
double cross(node p0, node p1, node p2);
double cross2(node p0, node p1, node p2);
void divide_printresult(nodearray pnode);
void init(nodearray* pnode, int len);
