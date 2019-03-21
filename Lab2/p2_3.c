#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** args) {
	
	int** arr;
	int i, j;
	int column, height;
	column = atoi(args[1]);
	height = column;
	arr = (int**)malloc(sizeof(int*)*height);

	for(i=0; i < height; i++) {
	arr[i] = (int*)malloc(sizeof(int)*column);
	}	
	printf("input a user name : ");
	for(i=0; i < height; i++) {
		scanf("%s", arr[i]);
	}

	printf("entered name : \n");	
	for(i=0; i < height; i++) { 
		printf("%s \n", arr[i]);
	}

	for(i=0; i < column ; i++) {
	free(arr[i]);
	arr[i]=NULL;
	}
	
	for(i=0; i < height; i++) {
	free(arr);
	arr=NULL;
	}
	return 0;
}
