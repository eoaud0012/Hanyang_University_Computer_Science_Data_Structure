#include <stdio.h>

void swap(int*, int*);
int main(int argv, char** argc) {
	int num1, num2;

	printf("enter 2 integers\n");
	scanf("%d%d", &num1,&num2);

	printf("you entered\n%d,%d\n",num1,num2);
	swap(&num1,&num2);
	printf("after swapping\n%d,%d\n",num1,num2);
return 0;
}

void swap(int* ptr1, int* ptr2) {
	int temp;

	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}
