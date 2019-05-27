#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sentinel 9999999
#define TRUE 1
#define FALSE 0
#define LeftChild(i) (2*i)

typedef struct Node {
	int vertex; // key gap
	int dist; // distance(weight)
	int prev;
} Node;

typedef struct Graph {
	int size;
	int** vertices;
	Node* nodes;
} Graph;

typedef struct Heap {
	int Capacity;
	int Size;
	Node* Element;
} Heap;
/*
Graph CreateGraph(int size);
void printShortestPath(Graph G);
Heap* createMinHeap(int heapSize);
void insertToMinHeap(Heap* minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);
int IsFull(Heap* H);
int IsEmpty(Heap* H);
*/
int IsFull(Heap* H) {
	return H->Size == H->Capacity-1 ? TRUE : FALSE;
}

int IsEmpty(Heap* H) {
	return H->Size == 0 ? TRUE : FALSE;
}

int getAdjacent(Graph G, int vertexNum) {
	int i = 0;
	int j = 0;
	for(i = 1; i < G.size; i++) 
		if(G.vertices[vertexNum][i] != 0) 
			return G.nodes[i].vertex;

}

Graph CreateGraph(int size) {
	int i = 0;
	int j = 0;
	Graph G;
	G.size = size;
	G.vertices = (int**)malloc(sizeof(int*)*(G.size));
	for(i = 1; i < G.size; i++)
		G.vertices[i] = (int*)malloc(sizeof(int)*(G.size));

	for(i = 1; i < G.size; i++)
		for(j = 1; j < G.size; j++)
			G.vertices[i][j] = 0;

	G.nodes = (Node*)malloc(sizeof(Node)*(G.size));
	for(i = 1; i < G.size; i++) {
		G.nodes[i].vertex = i;
		G.nodes[i].dist = sentinel;
		G.nodes[i].prev = 0;
	}
return G;
}

Heap* createMinHeap(int heapSize) {
	int i = 0;
	Heap* H;
	H = (Heap*)malloc(sizeof(Heap));
	H->Capacity = heapSize;
	H->Size = 0;
	H->Element = (Node*)malloc(sizeof(Node)*(H->Capacity));
	for(i = 1; i < heapSize; i++) {
		H->Element[i].vertex = i;
		H->Element[i].dist = sentinel;
		H->Element[i].prev = 0;	
	}
return H;
}

void insertToMinHeap(Heap* minHeap, int vertex, int distance) {
	int i = 0;
	if(IsFull(minHeap)) {
		printf("Min Heap is Full!");
		return;
	}	

	for(i = ++minHeap->Size; minHeap->Element[i/2].dist > distance; i /= 2)
		minHeap->Element[i] = minHeap->Element[i/2];

	minHeap->Element[i].vertex = vertex;
	minHeap->Element[i].dist = distance;	
}

Node deleteMin(Heap* minHeap) {
	int i = 0;
	int Child = 0;
	int MinElement = 0;
	int LastElement = 0;

	MinElement = minHeap->Element[1].dist;
	LastElement = minHeap->Element[minHeap->Size--].dist;
	
	for(i = 1; i*2 <= minHeap->Size; i = Child) {
		Child = i * 2;
		if(Child != minHeap->Size && minHeap->Element[Child+1].dist < minHeap->Element[Child].dist)
			Child++;
		if(LastElement > minHeap->Element[Child].dist)
			minHeap->Element[i] = minHeap->Element[Child];
		else break;
	}
	
	minHeap->Element[i].dist = LastElement;
	return minHeap->Element[1];
}
void PercDown(Heap* minHeap, int i, int N) {
	int Child;
	int Tmp;

	for(Tmp = minHeap->Element[i].dist; LeftChild(i) < N; i = Child) {
		Child = LeftChild(i);
		if(Child != N-1 && minHeap->Element[Child+1].dist > minHeap->Element[Child].dist)
		Child++;

		if(Tmp < minHeap->Element[i].dist)
			minHeap->Element[i] = minHeap->Element[Child];
		else break;
	}
}
void buildHeap(Heap* minHeap, int N) {
	int i;
	for(i = N/2; i > 0; i--)
		PercDown(minHeap, i, N);	
} 
void printShortestPath(Graph G) {
	int i = 0;
	int j = 0;
	int adjacentIndex = 0;
	G.nodes[1].dist = 0;
	G.nodes[1].prev = 0;
	Node tmp;
//	createMinHeap
	Heap* H;
	H = createMinHeap(G.size);
//	insertToMinHeap
	for(i = 1; i < G.size; i++)	
		insertToMinHeap(H, G.nodes[i].vertex, G.vertices[i][j]);

// set ShortedstPath
	adjacentIndex = getAdjacent(G, G.nodes[1].vertex);
	G.nodes[adjacentIndex].dist = G.vertices[1][adjacentIndex];
	G.nodes[adjacentIndex].prev = G.nodes[1].vertex;
	
	printf("%d->%d ", G.nodes[adjacentIndex].prev, G.nodes[adjacentIndex].vertex);
	printf("(cost: %d)\n", G.nodes[adjacentIndex].dist);

	while(!IsEmpty(H)) {
		tmp = deleteMin(H);
		adjacentIndex = getAdjacent(G, tmp.vertex);
		if(tmp.dist + G.vertices[tmp.vertex][adjacentIndex] < G.nodes[adjacentIndex].dist) {
			G.nodes[adjacentIndex].dist = tmp.dist + G.vertices[tmp.vertex][adjacentIndex];
			G.nodes[adjacentIndex].prev = tmp.vertex;

	printf("%d->%d ", G.nodes[adjacentIndex].prev, G.nodes[adjacentIndex].vertex);
	printf("(cost: %d)\n", G.nodes[adjacentIndex].dist);



			buildHeap(H, H->Size);
		} 
	}	


// print
//	G.nodes[1]->G.
}

void main(int argc, char* argv[]) {
	FILE *fi = fopen(argv[1], "r");
	Graph g;
	
	int size;
	fscanf(fi, "%d\n", &size);
	g = CreateGraph(size+1);
	char temp = 0;
	while( temp != '\n') {
		int node1, node2, weight;
		fscanf(fi, "%d-%d-%d", &node1, &node2, &weight);
		g.vertices[node1][node2] = weight;
		temp = fgetc(fi);
	}
	printShortestPath(g);
}
