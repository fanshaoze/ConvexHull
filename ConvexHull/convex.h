#include <stdio.h>


typedef struct 
{
	double x;
	double y;
}node;

int length;
double range;
int times;

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
int getMidIndex(node *nodes,int begin,int end);
node* divide_conquer(node* nodes, int begin, int end);
node* divide_graham_scan(node *nodes, int len);
void divide_quicksort(node central, node * nodes, int begin, int end, int min_y_index);
double get_angle(node central, node a, node b);

void swap(node *a, node *b);
void printresult(node *nodes, int *mark);
int generatenodes(node *nodes);
double cross(node p0, node p1, node p2);
void divide_printresult(node *nodes, int *mark, int begin, int end);
