#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
typedef struct _DisjointSet {
	int size_maze;
	int *ptr_arr;
} DisjointSets;

void init(DisjointSets *sets, DisjointSets *maze_print, int num) {
	int i = 0;

	sets->size_maze = num*num+1;
	maze_print->size_maze = 2*num*num+1;

	sets->ptr_arr = (int*)malloc(sizeof(int)*sets->size_maze);
	maze_print->ptr_arr = (int*)malloc(sizeof(int)*maze_print->size_maze);

	for(i = 1; i < sets->size_maze; i++)
		sets->ptr_arr[i] = 0;

	for(i = 1; i < maze_print->size_maze; i++)
		maze_print->ptr_arr[i] = -1;	
}

int find(DisjointSets *sets, int i) {
	while(sets->ptr_arr[i] > 0)
		i = sets->ptr_arr[i];
return i;
}

void Union(DisjointSets *sets, int i, int j) {
	int x = 0; int y = 0;
	x = find(sets, i);
	y = find(sets, j);

	if(sets->ptr_arr[y] < sets->ptr_arr[x])
		sets->ptr_arr[x] = y;
	else {
		if(sets->ptr_arr[y] == sets->ptr_arr[x])
			sets->ptr_arr[x]--;
		sets->ptr_arr[y] = x;
	}



/*	
	if(sets->ptr_arr[i] == 0 || sets->ptr_arr[j] == 0) {
		if(sets->ptr_arr[i] == 0 && sets->ptr_arr[j] != 0)
			sets->ptr_arr[i] = y;			
		else if(sets->ptr_arr[i] != 0 && sets->ptr_arr[j] == 0)
			sets->ptr_arr[j] = x;
		else if(sets->ptr_arr[i] == 0 && sets->ptr_arr[j] == 0) {
			sets->ptr_arr[i]--;
			sets->ptr_arr[j] = i;
		}
	}
	else if(sets->ptr_arr[j] != 0 && sets->ptr_arr[i] != 0)
		if(sets->ptr_arr[y] < sets->ptr_arr[x])
			sets->ptr_arr[x] = y;
		else if(sets->ptr_arr[x] == sets->ptr_arr[y]) {
			sets->ptr_arr[x]--;
			sets->ptr_arr[y] = x;
		}
		else if(sets->ptr_arr[y] > sets->ptr_arr[x])
			sets->ptr_arr[y] = x;
 */
}

void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num) {
	int i, j = 0;
	int direction[4];
	int random = 0; int random_direction = 0;
	int maze_num = 0; int chosen_maze_num = 0;
	while(1) {
		// end condition
		if( find(sets, 1) == find(sets, num*num) ) return;
		srand((unsigned int)time(NULL));
		random = rand()%(num*num)+1; // 1~36
		maze_num = random * 2 - 1; // right below maze num
	
		//left up corner
		if(random == 1) {
			direction[0] = maze_num;
			direction[1] = maze_num+1;	

			random_direction = rand() % 2; // 0~1
			chosen_maze_num = direction[random_direction];
		}	
		//left down corner
		else if(random == num*(num-1) + 1){ // random == 31
			direction[0] = maze_num-2*num;
			direction[1] = maze_num+1;
			random_direction = rand() % 2; // 0~1
			chosen_maze_num = direction[random_direction];
		}
	
		//right up corner
		else if(random == num) { // random == 6
			direction[0] = maze_num-1;
			direction[1] = maze_num;
			random_direction = rand() % 2; // 0~1
			chosen_maze_num = direction[random_direction];
		}
		
		//right down corner
		else if(random == num*num) { // random == 36
			direction[0] = maze_num-2*num;
			direction[1] = maze_num-1;
			random_direction = rand() % 2; // 0~1
			chosen_maze_num = direction[random_direction];
		}

		// no east
		else if(random % num == 0) { // random == 12, 18, 24, 30
			direction[0] = maze_num;
			direction[1] = maze_num-1;
			direction[2] = maze_num-2*num;
			random_direction = rand() % 3; // 0~2
			chosen_maze_num = direction[random_direction];
		}
	
		// no west
		else if(random % num == 1) { // random == 7, 13, 19, 25
			direction[0] = maze_num;
			direction[1] = maze_num+1;
			direction[2] = maze_num-2*num;
			random_direction = rand() % 3; // 0~2
			chosen_maze_num = direction[random_direction];
		}

		// no south
		else if(random / num == num-1) { // random == 32, 33, 34, 35
			direction[0] = maze_num-1;
			direction[1] = maze_num+1;
			direction[2] = maze_num-2*num;
			random_direction = rand() % 3; // 0~2
			chosen_maze_num = direction[random_direction];
		}

		// no north
		else if(random / num == 0) { // random == 2, 3, 4, 5
			direction[0] = maze_num;
			direction[1] = maze_num-1;
			direction[2] = maze_num+1;
			random_direction = rand() % 3; // 0~2
			chosen_maze_num = direction[random_direction];
		}

		// normal case
		else {
			direction[0] = maze_num;
			direction[1] = maze_num-1;
			direction[2] = maze_num+1;
			direction[3] = maze_num-2*num;
			random_direction = rand() % 4;

			chosen_maze_num = direction[random_direction];
		}

	// cycle check and update
	if(chosen_maze_num % 2 == 0) { // if direction is right or left
		
		if(maze_print->ptr_arr[chosen_maze_num] == 0) continue; // two random vertex are already in same group


		else if(find(sets, chosen_maze_num/2) == find(sets, (chosen_maze_num/2)+1)) continue;

		else {
			Union(sets, chosen_maze_num/2, (chosen_maze_num/2)+1);
			maze_print->ptr_arr[chosen_maze_num] = 0;
		}
	}
	else { // if direction is up or down
	
//		if(sets->ptr_arr[(chosen_maze_num-1)/2] != 0 && sets->ptr_arr[(chosen_maze_num+1)/2] != 0 && find(sets, (chosen_maze_num-1)/2 == find(sets, (chosen_maze_num+1)/2))) continue;

		if(maze_print->ptr_arr[chosen_maze_num] == 0) continue;

		else if(find(sets, (chosen_maze_num+(2*num)+1)/2) == find(sets, (chosen_maze_num+1)/2)) continue;

		else {
			Union(sets, (chosen_maze_num+(2*num)+1)/2, (chosen_maze_num+1)/2);
			maze_print->ptr_arr[chosen_maze_num] = 0;
		}
	}

	}
}

void printMaze(DisjointSets *maze_print, int num) {
	int i = 0; int j = 0; int k = 0; int x = 0;
/*	 _ _ _ _ _ _
	|_|_|_|_|_|_|
	|_|_|_|_|_|_|
	|_|_|_|_|_|_|
	|_|_|_|_|_|_|
	|_|_|_|_|_|_|
	|_|_|_|_|_|_|

*/

	for(i = 0; i < num; i++)
		printf(" _");
	printf(" ");

	printf("\n");
 
	for(j = 0; j < num; j++) {
		printf("|");
		for(i = 1; i < 2*num+1; i++) {
			if(i % 2 == 1)
				(maze_print->ptr_arr[2*j*num+i] == -1) ? printf("_") : printf(" ");
			else if(i % 2 == 0)
				(maze_print->ptr_arr[2*j*num+i] == -1) ? printf("|") : printf(" ");
		}
		printf("\n");
	}
	printf("\n");

}
void freeMaze(DisjointSets *sets, DisjointSets *maze_print) {
	free(sets->ptr_arr);
	free(sets);
	free(maze_print->ptr_arr);
	free(maze_print);
}
int main(int argc, char* argv[]) {
	int num, i;
	FILE *fi = fopen(argv[1], "r");
	DisjointSets *sets, *maze_print;
	fscanf(fi, "%d", &num);
	sets = (DisjointSets*)malloc(sizeof(DisjointSets));
	maze_print = (DisjointSets*)malloc(sizeof(DisjointSets));
	init(sets, maze_print, num);
	createMaze(sets, maze_print, num);
	printMaze(maze_print, num);
	freeMaze(sets, maze_print);

return 0;
}
