#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

//Lab
void InsertEdge(Graph G, int a, int b);
Graph CreateGraph(int* nodes, int i);
void DeleteGraph(Graph G);
void PrintGraph(Graph G);

//HW
void Topsort(Graph G);
Queue MakeNewQueue(int X);
int IsEmpty(Queue Q);
int IsFull(Queue Q);
int Dequeue(Queue Q);
void Enqueue(Queue Q, int X);
void DeleteQueue(Queue Q);
void MakeEmpty(Queue Q);

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


Graph CreateGraph(int* nodes, int length){
	int i, j;
	Graph G;

	G = (Graph)malloc(sizeof(struct _Graph));
	G->size = length;
	G->node = (int*)malloc(sizeof(int)*G->size);
	G->node = nodes;
	G->matrix = (int**)malloc(sizeof(int*)*G->size);
	for(i = 0; i < G->size; i++)
		G->matrix[i] = (int*)malloc(sizeof(int)*G->size);
	
	for(i = 0; i < G->size; i++)
		for(j = 0; j < G->size; j++)
			G->matrix[i][j] = 0;
return G;
}

void InsertEdge(Graph G, int a, int b){
	int i, j;
	
	for(i = 0; i < G->size; i++) 
		if(a == G->node[i])
			break;

	for(j = 0; j < G->size; j++)
		if(b == G->node[j])
			break;

	G->matrix[i][j] = 1;
}

void DeleteGraph(Graph G){
	int i;

	for(i = 0; i < G->size; i++)
		free(G->matrix[i]);
	free(G->node);
	free(G);
}

void PrintGraph(Graph G) {
	int i, j;

	printf("  ");
	for(i = 0; i < G->size; i++)
		printf("%d ", G->node[i]);
	printf("\n");
	
	for(i = 0; i < G->size; i++) {
		printf("%d ", G->node[i]);
		for(j = 0; j < G->size; j++)
			printf("%d ", G->matrix[i][j]);
		printf("\n");
	}
	printf("\n");	
}
int main(int argc, char **argv){
	int i = 0;
 	int* int_node;
	char input_node[100];
	char* token;
	Graph G = (Graph)malloc(sizeof(struct _Graph));
	FILE *fi = fopen(argv[1], "r");
	fgets(input_node, 100, fi);
	int_node = (int*)malloc(sizeof(int)*strlen(input_node));
	token = strtok(input_node, " ");
	while(token != NULL) {
		int_node[i++] = atoi(token);
		token = strtok(NULL, " ");
	}
	G = CreateGraph(int_node, i);

	while(!feof(fi)) {
		fscanf(fi, "%s", input_node);
		token = strtok(input_node, "-");
		if(token == NULL) break;
		int a = atoi(token);
		token = strtok(NULL, " ");
		if(token == NULL) break;
		int b = atoi(token);
		InsertEdge(G, a, b);
	}
	PrintGraph(G);
return 0;
}
