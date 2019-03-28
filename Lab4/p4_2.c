#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
typedef struct Stack {
	int* key; 
	int top;
	int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack *S, int X);
int IsFull(Stack *S);
int IsEmpty(Stack *S);
void PrintStack(Stack *S);
int Pop(Stack *S);
int Postfix(Stack *S, char input_str);
void DeleteSTack(Stack *S);


int IsEmpty(Stack *S) {
	return (S->top < 0) ? TRUE : FALSE;
}
int IsFull(Stack *S) {
	return (S->top >= S->max_stack_size-1) ? TRUE : FALSE;
}
Stack* CreateStack(int max) {
	Stack *S;
	S = (Stack*)malloc(sizeof(struct Stack));
	if(S == NULL) {
		fprintf(stderr, "Out of Memory");
		exit(1);
	}
	S->max_stack_size = max;
	S->top = -1;
	S->key = (int*)malloc(sizeof(int)*max);
	if(S->key == NULL) {
                fprintf(stderr, "Out of Memory");
                exit(1);
	}
	return S;
}
void Push(Stack *S, int X) {
	if(IsFull(S)) {
		fprintf(stderr, "Stack is Full");
                exit(1);
	}
	else	{
		S->key[++S->top] = X;
		printf("%d inserted \n", S->key[S->top]-'0');
	} 
}
int Pop(Stack *S) {
	if(IsEmpty(S)) {
		fprintf(stderr, "Stack is Empty");
		exit(1);
	}
	else 	S->key[S->top--];
	return S->key[S->top];
}
void DeleteStack(Stack *S) {
	if(IsEmpty(S)) {
                fprintf(stderr, "Stack is Empty");
                exit(1);
        }
	else {
		while(!IsEmpty(S)) {
			Pop(S);
		}
	}
}
int Postfix(Stack* S, char input_str) {
	int a, b;
	int result;
	switch(input_char) {
		case '+':

			break;
		case '-':

			break;
		case '*':

			break;
		case '/':

			break;
		case '%':

			break;
		default:

			break;
	}
	return result;
}
void main(int argc, char* argv[]) {
	FILE* fi = fopen(argv[1],"r");

	Stack* stack;
	char input_str[101];
	int max, i=0,a,b,result;
	
	fgets(input_str,101,fi);
	max = 10;
	stack = CreateStack(max);
	//p4_1 main code

	for(i=0; i<strlen(input_str)&&input_str[i]!='#';i++)
	{
		Push(stack, input_str[i]);
	}
	fclose(fi);
	DeleteStack(stack);

}
