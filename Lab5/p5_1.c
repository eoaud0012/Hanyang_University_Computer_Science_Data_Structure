#include <stdio.h>
#include <stdlib.h>
typedef struct CompleteTree 
{
	int Size;
	int nodeNum;
	int* Element;
};

typedef struct CompleteTree* Tree;

Tree CreateTree(int treeSize) {
	Tree tree = NULL;
	tree = (Tree)malloc(sizeof(Tree));
	tree->Size = treeSize+1;
	tree->nodeNum = 1;
	if(tree == NULL) {
		printf("Out Of Memory!");
		exit(1);
	}
	tree->Element = malloc(sizeof(int)*treeSize);
	if(tree->Element == NULL) {
		printf("Out Of Memory!");
		exit(1);
	}
	return tree;	
}
void Insert(Tree tree, int value) {
	if(tree->nodeNum >= tree->Size) {
		printf("Tree is Full\n");
		return;
	}
		tree->Element[tree->nodeNum] = value;
		tree->nodeNum++;	
}

void printPreorder(Tree tree, int index) {
	printf("%d ", tree->Element[index]);
	
	if(tree->Element[index*2] && (index*2) < (tree->Size-1)) {
	printPreorder(tree, index*2);
	}
	if(tree->Element[(index*2)+1] && (index*2+1)<(tree->Size-1)) {
	printPreorder(tree, (index*2)+1);
	}
}

//void printInorder(Tree tree, int index);
//void printPostorder(Tree tree, int index);

void printTree(Tree tree) {
	printf("Preorder : ");
	printPreorder(tree, 1);
	printf("\t");
//	printInorder(tree, 0);
//	printPostorder(tree, 0);
}
void freeTree(Tree tree) {
	free(tree->Element);
	free(tree);
}

void main(int argc, char* argv[])
{
	FILE *fi;
	Tree tree;
	int treeSize;
	int tempNum;

	fi = fopen(argv[1], "r");
	fscanf(fi, "%d", &treeSize);
	tree = CreateTree(treeSize);
	while(fscanf(fi, "%d", &tempNum) == 1)
	{
		Insert(tree, tempNum);
	}
	printTree(tree);
	freeTree(tree);
}
