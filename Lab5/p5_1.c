#include <stdio.h>
#include <stdlib.h>
struct CompleteTree 
{
	int Size;
	int nodeNum;
	int* Element;
};
typedef struct CompleteTree* Tree;
Tree CreateTree(int treeSize) {
	Tree t;
	t = (Tree)malloc(sizeof(Tree));
	t->Size = treeSize;
	t->nodeNum = 1;
	t->Element = (int*)malloc(sizeof(int)*t->Size);
return t;
}
void Insert(Tree tree, int value) {
	if(tree->Size < tree->nodeNum)
		printf("Tree is Full\n");
	else tree->Element[tree->nodeNum++] = value;
}
void printPreorder(Tree tree, int index) {
	if(index < tree->nodeNum) {
		printf("%d ", tree->Element[index]);
		printPreorder(tree, index*2);
		printPreorder(tree, index*2+1);
	}
}
void printInorder(Tree tree, int index) {
	if(index < tree->nodeNum) {
		printInorder(tree, index*2);
		printf("%d ", tree->Element[index]);
		printInorder(tree, index*2+1);
	}
} 
void printPostorder(Tree tree, int index) {
	if(index < tree->nodeNum) {
		printPostorder(tree, index*2);
		printPostorder(tree, index*2+1);
		printf("%d ", tree->Element[index]);
	}
}

void printTree(Tree tree) {
	printf("Preorder : ");
	printPreorder(tree, 1);
	printf("\n");
//	printf("Inorder : ");
//	printInorder(tree, 1);
//	printf("\n");
//	printf("Postorder : ");
//	printPostorder(tree, 1); 
//	printf("\n");
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
