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
int IsEmpty(List L) {
	return (L->element == -1 && L->next == NULL) ? TRUE : FALSE;	
}
int IsLast(Position P, List L) {
	return (P->element != -1 && P->next == NULL) ? TRUE : FALSE;
}
Position Find(ElementType X, List L) {
	 
	if(X == -1) 
		return L;
	else {
		Position target;
		target = L;
	while(target != NULL && target->element != X) {
		target = target->next;
	}
	if(target == NULL)
		printf("Could not find %d in the list\n", X);
	return target;
}
}
Position FindPrevious(ElementType X, List L) {
	Position target;
	target = L;
	while(target->next != NULL && target->next->element != X) {
		target = target->next;
	}
	if(target == NULL)
		printf("Could not find %d in the list\n", X);

	return target;
}
void Delete(ElementType X, List L) {
	Position P, targetCell;
	P = FindPrevious(X, L);
	targetCell = P->next;
	if(targetCell == NULL) {
		fprintf(stderr, "Deletion failed : element %d is not in the list\n", X);
		return;
	};
	if(!IsLast(targetCell, L)) {
		P->next = targetCell->next;
		free(targetCell);
	}
	else {
		P->next = NULL;
		free(targetCell);	
	}
}
void DeleteList(List L) {
	Position x, tmpCell;
	x=L->next;
	while(x != NULL) {
		tmpCell = x->next;
		free(x);
		x = tmpCell;
	}
}
List MakeEmpty(List L) {
	L = (List)malloc(sizeof(struct Node));
	L->element = -1;
	return L;
}

void Insert(ElementType X, List L, Position P) {
	if(P == NULL) { 
		fprintf(stderr, "Insertion(%d) Failed : cannot find the location to be inserted\n", X); 
		return;
	}
	Position tmpcell;
	tmpcell = (Position)malloc(sizeof(struct Node));
	if(tmpcell == NULL) 
			fprintf(stderr, "Out of Space");
	if(P == L) {
	tmpcell->element = X;
		if(!IsEmpty(L)) {
			Position temp;
			temp = L->next;
			tmpcell->next = temp;
			L->next = tmpcell;
		}	
		else {	
			L->next = tmpcell;
			tmpcell->next = NULL;
		}
	}
	else {
		tmpcell->element = X;
		P->next = tmpcell;
}
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
			tmp = Find(key2, header);
			Insert(key1, header, tmp);
			Insert(key1,header,header);
			break;
		case 'd':
			fscanf(input, "%d", &key1);
			Delete(key1, header);
			break;
		case 'f':
			fscanf(input, "%d", &key1);
			tmp = FindPrevious(key1, header);
			if(IsLast(tmp, header))
				printf("Could not find %d in the list\n", key1);
			else {
				if(tmp->element>0)
					printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
				else
					printf("Key of the previous node of %d is header.\n", key1);
			}
		case 'p':
			PrintList(header);
			break;
		default:
			break;
		}
	}
	DeleteList(header); //free all memory used by linked list
	fclose(input);
	return 0;
}

