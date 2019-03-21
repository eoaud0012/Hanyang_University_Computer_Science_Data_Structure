#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147438647
#define FALSE 0
#define TRUE 1
int IsZero(int);
int Equal(int, int);
int Successor(int);
int Add(int, int);
int Subtract(int, int);


int main(int argc, char** args) {

	int x = atoi(args[1]);
	int y = atoi(args[2]);

	printf("%d\n", x);
	printf("%d\n", y);

	printf("IS %d zero? %s\n",x,IsZero(x) ? "True":"False");
	printf("IS %d zero? %s\n",y,IsZero(y) ? "True":"False");
	printf("Does %d eqaul? %d? %s\n",x,y,Equal(x,y) ? "True":"False");
	printf("%d's next number is %d\n",x,Successor(x));
	printf("%d's next number is %d\n",y,Successor(y));
	printf("%d + %d = %d\n", x, y, Add(x,y));
	printf("%d - %d = %d\n", x, y, Subtract(x,y));

	return 0;

	
}

int IsZero(int a) {
	return (a == 0) ? TRUE : FALSE;
}

int Equal(int a, int b) {
	return (a == b) ? TRUE : FALSE;
}

int Successor(int a) {
	return ((a+1) < INT_MAX) ? a+1 : a;
}

int Add(int a, int b) {
	return ((a+b) < INT_MAX) ? a+b : a;
}

int Subtract(int a, int b) {
	return (a > b) ? a-b : 0;
}
