#include <stdio.h>

int main(int argc, char** args[]) {

	char* c1[30];
	printf("input a user name\n");
	scanf(" %[^\n]s", c1);

	printf("a user name : ");
	printf("%s\n", c1);
	

return 0;
}
