#include <stdio.h>
#include <stdlib.h>
typedef struct AVLNode* AVLTree;
typedef struct AVLNode* Position;
typedef int ElementType;
struct AVLNode
{
	ElementType Element;
	AVLTree Left;
	AVLTree Right;
	int Height;
};
ElementType Height(Position node) {
	if(node == NULL)
		return -1;
return node->Height;
}
ElementType Max(ElementType leftheight, ElementType rightheight) {
	if(leftheight > rightheight)
		return leftheight;
	else return rightheight;
}
Position SingleRotateWithLeft(Position node) {
/*LL*/
	Position tmp;
	
	tmp = node->Left;
	node->Left = tmp->Right;
	
	tmp->Right = node;

	node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
	tmp->Height = Max(Height(tmp->Left), Height(tmp->Right)) + 1;

return tmp;
}
Position SingleRotateWithRight(Position node) {
/*RR*/
	
	Position tmp;
	
	tmp = node->Right;
	node->Right = tmp->Left;
	
	tmp->Left = node;

	node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
	tmp->Height = Max(Height(tmp->Left), Height(tmp->Right)) + 1;

return tmp;

}
AVLTree Insert(ElementType X, AVLTree T) {
/*Insert a new node to the AVLTree. Print tree whenever inserting a new node. **key duplication - "[Error] [key] already in the tree!"** */

	//boundary
	if(T == NULL) {
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		if(T == NULL)
			printf("Out of Space!");
		T->Element = X;
		T->Left = T->Right = NULL;
		T->Height = 0;
	}
	//recursive
	else if(X < T->Element) {
		T->Left = Insert(X, T->Left);
		if(Height(T->Left) - Height(T->Right) == 2)
			if(X < T->Left->Element)
				T = SingleRotateWithLeft(T);
			//else T = DoubleRotateWithLeft(T);
	}
	else if(X > T->Element) {
		T->Right = Insert(X, T->Right);
		if(Height(T->Right) - Height(T->Left) == 2)
			if(X > T->Right->Element)
				T = SingleRotateWithRight(T);
			//else T = DoubleRotateWithRight(T);
	}
	else { /*already in the tree */
	printf("[Error] %d already in the tree!\n", T->Element);
	return T;
	}
	// Height resetting
	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
return T;
}
void PrintInorder(AVLTree T) {
/*Print the tree by inorder traversal. Print height of the node inside bracket.*/
	if(T != NULL) {
		PrintInorder(T->Left);
		printf("%d(%d) ", T->Element, T->Height);
		PrintInorder(T->Right);
	}
}
void DeleteTree(AVLTree T) {
/*Free tree */
free(T);
}
//Position DoubleRotateWithLeft(Position node) {
//
//}
//Position DoubleRotateWithRight(Position node) {
//
//}
int main(int argc, char **argv) {
	FILE *fp = fopen(argv[1], "r");
	AVLTree myTree = NULL;
	int num;

	if (fp == NULL) {
		printf("There is no file : %s\n", argv[1]);
		exit(-1);
	}

	while (fscanf(fp, "%d", &num) != EOF) {
		myTree = Insert(num, myTree);
		PrintInorder(myTree);
		printf("\n");
	}

	DeleteTree(myTree);
	return 0;
}
