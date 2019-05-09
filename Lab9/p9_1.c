#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue
{
	int* key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};

struct _Graph
{
	int size;
	int* node;
	int** matrix;
};


/*Lab*/
void PrintGraph(Graph G) {
	int length = sizeof(G->node)/sizeof(int);
	int i, j;
	printf(" ");
	for(i = 0; i < length; i++)
		printf("%d ", G->node[i]);
	printf("\n");
	while(i != length) {
		i = 0;
		printf("%d ", G->node[i]);
		for(j = 0; j < length; j++)
			printf("%d ", G->matrix[i][j]);
		i++;
	}
}
Graph CreateGraph(int* nodes, int length) {
/*Create a graph with nodes*/
	int i, j;
	Graph G;
	G = (Graph)malloc(sizeof(struct _Graph));
	G->node = nodes;
	G->size = length;
	G->matrix = (int**)malloc(sizeof(int)*(G->size));
	for(i = 0; i < G->size; i++)
		G->matrix[i] = (int*)malloc(sizeof(int)*(G->size));

	for(i = 0; i < G->size; i++) 
		for(j = 0; j < G->size; j++)
			G->matrix[i][j] = 0;
	
return G;
}
void InsertEdge(Graph G, int a, int b) {
/*Insert a edge*/
	int i, j, x, y;
	//what is the index of a
	for(i = 0; i < G->size; i++)
		if(a = G->node[i]) {
			x = i;
			break;
		}
	for(j = 0; j < G->size; j++)
		if(b = G->node[j]) {
			y = j;
			break;
		}
	G->matrix[x][y] = 1;
	G->matrix[y][x] = 1;
}
void DeleteGraph(Graph G) {
int i;
for(i = 0; i < G->size; i++) 
	free(G->matrix[i]);
free(G->matrix);
free(G);
}

/*HW*/
/*
void Topsort(Graph G) {
//Print the graph by topological sort. Sort the smaller number key if same priority.

}
Queue MakeNewQueue(int X) {
//Create a new queue with the size of X
}
int IsEmpty(Queue Q) {

}
int IsFull(Queue Q) {

}
int Dequeue(Queue Q) {
// the node it the front
}
void Enqueue(Queue Q, int X) {
// a new element at the end of the element in the queue
}
void DeleteQueue(Queue Q) {

}
void MakeEmpty(QUeue Q) {

}
*/
void main(int argc, char* argv[])
{
	int i=0;
	int* int_node;
	char input_node[100];
	char* token;
	Queue q;
 	Graph g;
	g = (Graph)malloc(sizeof(struct _Graph));
	q = (Queue)malloc(sizeof(struct _Queue));
	FILE *fi = fopen(argv[1], "r");
	fgets(input_node, 100, fi);
	int_node = (int*)malloc(sizeof(int)*strlen(input_node));
	token = strtok(input_node, " ");
	while(token != NULL) {
		int_node[i++] = atoi(token);
		token = strtok(NULL, " ");
	}
	g = CreateGraph(int_node, i);

	while(!feof(fi)) {
		fscanf(fi, "%s", input_node);
		token = strtok(input_node, "-");
		if(token == NULL) break;
		int a = atoi(token);
		token = strtok(NULL, " ");
		if(token == NULL) break;
		int b = atoi(token);
		InsertEdge(g, a, b);
	}
	PrintGraph(g);
	
	free(q);
	free(g);
};
	
