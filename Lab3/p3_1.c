#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node {
	ElementType element;
	Position	 next;
};
List MakeEmpty(List L) {
	Position header;
	header = malloc(sizeof(struct Node));
	return header;
}

void Insert(ElementType X, List L, Position P) {
	Position tmpcell;
	Position x;
	x=L;
	tmpcell = (Position)malloc(sizeof(struct Node));
	
	if(tmpcell == NULL) {
		fprintf(stderr, "Out of Space");
	}
	tmpcell->element = X;
	tmpcell->next = x->next;
	P->next = tmpcell;
}
void PrintList(List L){
	Position x;
	x = L->next;

	while(x != NULL) {
		printf("key:%d \t", x->element);
		x = x->next;
	}
	printf("\n");
}
int main(int argc, char *argv[]) {
	char command;
	int key1, key2;
	FILE *input;
	Position header; 
	Position tmp;
	if(argc == 1) {
		printf("No input file\n");
		return 0;
	}
	else
		input = fopen(argv[1], "r");
	header = MakeEmpty(header);
	while(1) {
		command = fgetc(input);
		if(feof(input)) break;
		switch(command) {
		case 'i':
			fscanf(input, "%d %d", &key1, &key2);
				//tmp = Find(key2, header); hw3
				//Insert(key1, header, tmp); hw3
			Insert(key1,header,header);
			break;
//		case 'd':
//			fscanf(input, "%d", &key1);
//			Delete(key1, header);
//			break;
//		case 'f':
//			fscanf(input, "%d", &key1);
//			tmp = FindPrevious(key1, header);
//			if(IsLast(tmp, header))
//				printf("Could not find %d in the list\n", key1);
//			else {
//				if(tmp->element>0)
//					printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
//				else
//					printf("Key of the previous node of %d is header.\n", key1);
//			}
		case 'p':
			PrintList(header);
			break;
		default:
			break;
		}
	}
//	DeleteList(header); //free all memory used by linked list
	fclose(input);
	return 0;
}

