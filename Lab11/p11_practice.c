#include <stdio.h>

int main(void) {
	int i = 0;
	int j = 0;
	for(i = 0; i < 6; i++)
		printf(" _");
	printf(" ");

	printf("\n");

	for(j = 0; j < 6; j++) {
		for(i = 0; i < 6; i++)
			printf("|_");
		printf("|");

		printf("\n");
	}
return 0;
}
