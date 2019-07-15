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
	int next;
	int visited;
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

int getAdjacent(Graph G, int vertexNum, int startNum) {
	int i = 0;
	int j = 0;
	for(i = startNum; i < G.size; i++) {
		if(G.vertices[vertexNum][i] != 0 && G.nodes[i].visited == FALSE) 
			return G.nodes[i].vertex;
	}
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
		G.nodes[i].visited = FALSE;
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

	for(i = 1; i < H->Capacity; i++) {
		H->Element[i].vertex = sentinel;
		H->Element[i].dist = sentinel;
		H->Element[i].prev = sentinel;
		H->Element[i].next = sentinel;
		H->Element[i].next = FALSE; 
	}

return H;
}

void insertToMinHeap(Heap* minHeap, Node node) {
	int i = 0;
	if(IsFull(minHeap)) {
		printf("Min Heap is Full!");
		return;
	}

	for(i = 0; i < minHeap->Size; i++) {
		if(minHeap->Element[i].vertex == node.vertex) {
			minHeap->Element[i] = node;
			return;
		}
	}

	for(i = ++minHeap->Size; i >= 2 && minHeap->Element[i/2].dist > node.dist; i /= 2)
		minHeap->Element[i] = minHeap->Element[i/2];

	minHeap->Element[i] = node;

}

Node deleteMin(Heap* minHeap) {
	int i = 0;
	int Child = 0;
	Node MinNode;
	Node LastNode;

	MinNode = minHeap->Element[1];
	LastNode = minHeap->Element[minHeap->Size--];

	for(i = 1; i*2 <= minHeap->Size; i = Child) {
		Child = i * 2;
		if(Child != minHeap->Size && minHeap->Element[Child+1].dist < minHeap->Element[Child].dist)
			Child++;
		if(LastNode.dist > minHeap->Element[Child].dist)
			minHeap->Element[i] = minHeap->Element[Child];
		else break;
	}
	
	minHeap->Element[i] = LastNode;
	return MinNode;
}
/*
void PercDown(Heap* minHeap, int i, int N) {
	int Child;
	Node Tmp;

	for(Tmp = minHeap->Element[i]; LeftChild(i) < N; i = Child) {
		Child = LeftChild(i);
		if(Child != N-1 && minHeap->Element[Child+1].dist < minHeap->Element[Child].dist)
			Child++;

		if(Tmp.dist > minHeap->Element[Child].dist)
			minHeap->Element[i] = minHeap->Element[Child];
		else break;
	}
}
void buildHeap(Heap* minHeap, int N) {
	int i;
	for(i = N/2; i > 0; i--)
		PercDown(minHeap, i, N);	
}
*/

void printResultPath(Graph G, int target) {
	int arr[G.size];
	int size = 0;
	int dist = G.nodes[target].dist;
	arr[++size] = target;	

	if(dist == sentinel) {
		printf("cannot reach to node %d\n", target);
		return;
	}

	while(TRUE) {

		if(G.nodes[target].prev != 0) {
			target = G.nodes[target].prev;
			arr[++size] = target;
		}	
		else break;
	}

	while(TRUE) {	
		printf("%d", arr[size--]);
		if(size == 0) {
			printf(" cost : (%d)\n", dist);
			return;
		}
		else printf("->");
	}
}

void printShortestPath(Graph G) {
	int i = 0;
	int j = 0;
	int adjacentIndex = 0;
	int count = 2;
	Node tmp;

//	createMinHeap
	Heap* H;
	H = createMinHeap(G.size);

// initialize
	// Graph
	G.nodes[1].dist = 0;
	G.nodes[1].prev = 0;
	// visit
	G.nodes[1].visited = TRUE;
/*
	1->2 (cost : 3)
	1->2->3 (cost : 5)
	cannot reach to node 4
*/

// insertToMinHeap(Only source)
	insertToMinHeap(H, G.nodes[1]);
	
	while(H->Size > 0) {
		tmp = deleteMin(H);
		G.nodes[tmp.vertex].visited = TRUE;
		for(i = 2; i < G.size; i++) {
			adjacentIndex = getAdjacent(G, tmp.vertex, i);		
			if(G.nodes[adjacentIndex].dist > tmp.dist + G.vertices[tmp.vertex][adjacentIndex]) {
				G.nodes[adjacentIndex].dist = tmp.dist + G.vertices[tmp.vertex][adjacentIndex];
				G.nodes[adjacentIndex].prev = tmp.vertex;
				insertToMinHeap(H, G.nodes[adjacentIndex]);			
			}
		}
	}
	for(j = count; j < G.size; j++)
		printResultPath(G, j);
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
