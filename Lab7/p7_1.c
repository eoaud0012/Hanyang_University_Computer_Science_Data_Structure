#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct
{
		int Capacity;
		int Size;
		int *Element;
}Heap;
Heap* CreateHeap(int heapSize) {
	Heap *h;
	h = (Heap*)malloc(sizeof(Heap));
	h->Element = (int*)malloc(sizeof(int)*heapSize);
	h->Capacity = heapSize;
	h->Size = 0;
	h->Element[h->Size] = -1;
return h;
}
int Find(Heap *heap, int value) {
/* Find the key int the heap. Return 1 if the value exists.
Otherwise, return 0.*/
	int i;
	for(i = heap->Size; i > 0; i--) {
		if(value == heap->Element[i]) 
			return 1;
	}
return 0;
}
void Insert(Heap *heap, int value) {
/* You should find the right position for
the new key to maintain the max heap. If heap
is full, print an error message. If the key
already exists in the heap, print an error message.*/
int i;
	if(heap->Size == heap->Capacity)
		printf("Insertion Error : Max Heap is full.\n");
	if(Find(heap, value) == 1) {
		printf("%d is already in the heap\n", value);
		return;
	}
	if(heap->Size < heap->Capacity) {
		for(i = ++heap->Size; heap->Element[i/2] < value; i /= 2) {
			heap->Element[i] = heap->Element[i/2];
			if(i == 0) { heap->Element[1] = value; break; }
		}
		heap->Element[i] = value;
		printf("insert %d\n", heap->Element[i]);
	}
}

//int DeleteMax(Heap *heap) {
///*Delete the max in root node and reconstruct the heap to maintain
//max heap. If your list does not have any element, just print an
//error message.*/
//}
//void PrintHeap(Heap *heap) {
///*Print the entire heap in level order traversal. If your queue
//is empty, just print an error message*/
//}

void main(int argc, char* argv[])
{
		FILE *fi = fopen(argv[1], "r");
		char cv;
		Heap* maxHeap;
		int heapSize, key;
		while(!feof(fi))
		{
			fscanf(fi, "%c", &cv);
			switch(cv){
			case 'n' :
					fscanf(fi, "%d", &heapSize);
					maxHeap = CreateHeap(heapSize);
					break;
			case 'i' :
					fscanf(fi, "%d", &key);
					Insert(maxHeap, key);
					break;
//			case 'd' :
//					DeleteMax(maxHeap);
//					break;
//			case 'p' :
//					PrintHeap(maxHeap);
//					break;
			case 'f' :
					fscanf(fi, "%d", &key);
					if(Find(maxHeap, key))
						printf("%d is in the heap.\n", key);
					else
						printf("%d is not in the heap.\n", key);
					break;
			}
}

}

