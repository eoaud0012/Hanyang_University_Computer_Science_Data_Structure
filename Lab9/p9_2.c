#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

//Lab
void InsertEdge(Graph G, int a, int b);
Graph CreateGraph(int* nodes, int i);
void DeleteGraph(Graph G);
void PrintGraph(Graph G);

//HW
int* checkIndegree(Graph G);
void Topsort(Graph G, Queue Q);
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
   int front;
   int rear;
   int qsize;
   int max_queue_size;
};

struct _Graph
{
   int size;
   int* node;
   int* visited;
   int** matrix;
};


Graph CreateGraph(int* nodes, int length){
	int i, j;
	Graph G;

	G = (Graph)malloc(sizeof(struct _Graph));
	G->size = length;
	G->node = (int*)malloc(sizeof(int)*G->size);
	G->node = nodes;
	G->visited = (int*)malloc(sizeof(int)*G->size);
	G->matrix = (int**)malloc(sizeof(int*)*G->size);
	for(i = 0; i < G->size; i++)
		G->matrix[i] = (int*)malloc(sizeof(int)*G->size);
	
	for(i = 0; i < G->size; i++)
		G->visited[i] = FALSE;
	
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
}

Queue MakeNewQueue(int X) {
	Queue Q;
	Q = (Queue)malloc(sizeof(struct _Queue));
	Q->max_queue_size = 100;
	Q->key = (int*)malloc(sizeof(int)*(Q->max_queue_size));
	Q->front = 0;
	Q->rear = -1;
	Q->qsize = 0;	
return Q;	
}
int IsEmpty(Queue Q) {
	return (Q->rear == -1 && Q->front == 0) || (Q->rear == Q->front-1) ? TRUE : FALSE;
}
int IsFull(Queue Q) {
	return (Q->qsize == Q->max_queue_size-1) ? TRUE : FALSE;
}
int Dequeue(Queue Q) {
	int data;
	if(Q->front+1 == Q->max_queue_size)
		(Q->front) %= 100;
	Q->qsize--;
return Q->key[Q->front++];
}
void Enqueue(Queue Q, int X) {
	if(Q->rear+1 == Q->max_queue_size)
		(Q->rear) %= 100;
 	Q->key[++Q->rear] = X;
	Q->qsize++;
}
void DeleteQueue(Queue Q) {
	free(Q->key);
}
void MakeEmpty(Queue Q) {
	while(!IsEmpty(Q))
		Dequeue(Q);
}

int* checkIndegree(Graph GG) {
	int i, j;
	int* int_indegree;
	int* int_indegree_copy;
	Graph G = GG;
	int_indegree = (int*)malloc(sizeof(int)*(G->size));
	int_indegree_copy = (int*)malloc(sizeof(int)*(G->size));

	for(i = 0; i < G->size; i++) {
		int_indegree[i] = 0;
		int_indegree_copy[i] = 0;
	}

	for(i = 0; i < G->size; i++)
		for(j = 0; j < G->size; j++)
			if(G->matrix[j][i] != 0)
				int_indegree[i]++;

	for(i = 0; i < G->size; i++)
		int_indegree_copy[i] = int_indegree[i];

	free(int_indegree);

return int_indegree_copy;
}

void Topsort(Graph GG, Queue QQ) {
	int i, j, k = 0;
	int vertex;
	int* int_indegree;
	Queue Q;
	Graph G;
	G = (Graph)malloc(sizeof(struct _Queue));
	Q = (Queue)malloc(sizeof(struct _Queue));
	G = GG;
	Q = QQ;
	int_indegree = checkIndegree(G);
	
	for(i = 0; i < G->size; i++) { 
		if(int_indegree[i] == 0) {
			Enqueue(Q, G->node[i]);
			G->visited[i] = TRUE;
		}			
	}
	
	while(!IsEmpty(Q)) {
		vertex = Dequeue(Q);
		for(i = 0;	i < G->size; i++)  {
			if(vertex == G->node[i]) {
				k = i;
				break;
			}
		}
		for(j = 0; j < G->size; j++) 
			G->matrix[k][j] = 0;

		G->visited[k] = TRUE;

		printf("%d ", vertex); 

		int_indegree = checkIndegree(G);

		for(k = 0; k < G->size; k++) {
			if(G->visited[k] != TRUE && int_indegree[k] == 0) {
				Enqueue(Q, G->node[k]);
				G->visited[k] = TRUE;
			}
		}
		}
	
		printf("\n");
	}

int main(int argc, char **argv){
	int i, j = 0;
 	int* int_node;
	char* token;
	char input_node[100];
	Graph G = (Graph)malloc(sizeof(struct _Graph));
	Queue Q = (Queue)malloc(sizeof(struct _Queue));
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
	Q = MakeNewQueue(-1);	
	Topsort(G, Q);
	DeleteQueue(Q);
	DeleteGraph(G);
	free(int_node);
return 0;
}
