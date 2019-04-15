#include <stdio.h>
#include <stdlib.h>

typedef struct BinarySearchTree* Tree;
struct BinarySearchTree
{
	int value;
	Tree left;
	Tree right;
};
int count1 = 0;
int count2 = 0;
Tree findNode(Tree root, int key) {
	if(root == NULL) {
		printf("%d is not in the tree\n", key);
		return root;
	}
	else if(root->value == key) {
		printf("%d is in the tree\n", key);
		return root;
	}
	if(root->value < key)
		root->right = findNode(root->right, key);
	else if(root->value > key)
		root->left = findNode(root->left, key);

}
Tree insertNode(Tree root, int key) {
	if(root == NULL) {
		root = (Tree)malloc(sizeof(Tree));
		if(root == NULL) {
			printf("Out of space\n");
			return NULL;
		}
		root->left = NULL;
		root->right = NULL;
		root->value = key;
		printf("insert %d\n", root->value); 
	} else {
		if(root->value < key)
			root->right = insertNode(root->right, key);

		else if(root->value > key)
			root->left = insertNode(root->left, key);
		if(root->value == key) { 
			printf("Insertion Error : There is already %d in the tree\n", key); 
		}

	}
	return root;
}
void printInorder(Tree root) {
	if(root) {
		printInorder(root->left);
		printf("%d ", root->value);
		printInorder(root->right);
	}
}
void deleteTree(Tree root) {
	free(root);
}		
Tree getMaxValueInTree(Tree parentNode, Tree root) {
	if(root == NULL)
		return parentNode;
	else { 
		while(root->right != NULL)
			root = root->right;	
		
return root;	
}
Tree deleteNode(Tree root, int key) {
	Tree max, tmp;
	// boundary
	if(root == NULL)
		printf("Deletion Error : %d does not exist in the tree\n", key);
	
	// recursive
	else if(root->value > key) 
			root->left = deleteNode(root->left, key);
	else if(root->value < key)
			root->right = deleteNode(root->right, key);
	else if(root->value == key && root->left != NULL && root->right != NULL) {
	count1++;	
	printf("Delete %d\n", key);
	max = getMaxValueInTree(root, root->left);
	root->value = max->value;
	root->left = deleteNode(root->left, root->value);
}
	else if(root->value == key && (root->left == NULL || root->right == NULL)) {
		count2++;
		if(count1 != count2)
			printf("Delete %d\n", key);
		tmp = root;
		if(root->left == NULL)
			root = root->right;
	else if(root->right == NULL)
			root = root->left;
		free(tmp);
		tmp = NULL;
}

count1 = 0;
count2 = 0;			
return root;
}
void main(int argc, char * argv[])
{
	FILE *fi = fopen(argv[1], "r");
	char cv;
	int key;

	Tree root = NULL;
	
	while(!feof(fi))
	{
		fscanf(fi, "%c", &cv);
		switch(cv) {
		case 'i':
				fscanf(fi, "%d", &key);
				root = insertNode(root, key);
				break;
		case 'd':
				fscanf(fi, "%d", &key);
				deleteNode(root, key);
				break;
		case 'f':
				fscanf(fi, "%d", &key);
				findNode(root, key);
				break;
		case 'p':
				fscanf(fi, "%c", &cv);
				if(cv == 'i')
					printInorder(root);
				printf("\n");
				break;
		}
	}
deleteTree(root);
}

