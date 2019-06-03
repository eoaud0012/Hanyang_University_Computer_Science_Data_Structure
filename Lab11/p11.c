#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct _DisjointSet {
	int size_maze;
	int *ptr_arr;
} DisjointSets;

void init(DisjointSets *sets, DisjointSets *maze_print, int num) {
	int i = 0;

	sets->size_maze = num*num;
	maze_print->size_maze = num*num;

	sets->ptr_arr = (int*)malloc(sizeof(int)*sets->size_maze);
	maze_print->ptr_arr = (int*)malloc(sizeof(int)*(2*maze_print->size_maze));

	for(i = 0; i < sets->size_maze; i++)
		sets->ptr_arr[i] = 0;

	for(i = 0; i < 2*maze_print->size_maze; i++)
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

	// cycle check
	if(sets->ptr_arr[i] < 0 || sets->ptr_arr[j] < 0) return;
	
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
		sets->ptr_arr[
}


void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num) {
	int i, j = 0;
	int direction[4];
	int random = 0; int random_direction = 0;
	int maze_num = 0; int chosen_maze_num = 0;
	srand((unsigned int)time(NULL));
	while(1) {

		random = rand()%(num*num); // 0~35
		maze_num = random * 2;
	
		//left up corner
		if(random == 0) {
			direction[0] = maze_num;
			direction[1] = maze_num+1;	

			random_direction = rand() % 2; // 0~1
			chosen_maze_num = direction[random_direction];
		}	
		//left down corner
		else if(random == num*(num-1)) {
			direction[0] = maze_num-2*num;
			direction[1] = maze_num+1;
			random_direction = rand() % 2; // 0~1
			chosen_maze_num = direction[random_direction];
		}
	
		//right up corner
		else if(random == num-1) {
			direction[0] = maze_num-1;
			direction[1] = maze_num;
			random_direction = rand() % 2; // 0~1
			chosen_maze_num = direction[random_direction];
		}
		
		//right down corner
		else if(random == num*num-1) {
			direction[0] = maze_num-2*num;
			direction[1] = maze_num-1;
			random_direction = rand() % 2; // 0~1
			chosen_maze_num = direction[random_direction];
		}

		// no east
		else if(random % num == num-1) {
			direction[0] = maze_num;
			direction[1] = maze_num-1;
			direction[2] = maze_num-2*num;
			random_direction = rand() % 3; // 0~1
			chosen_maze_num = direction[random_direction];
		}
	
		// no west
		else if(random % num == 0) {
			direction[0] = maze_num;
			direction[1] = maze_num+1;
			direction[2] = maze_num-2*num;
			random_direction = rand() % 3; // 0~1
			chosen_maze_num = direction[random_direction];
		}

		// no south
		else if(random / num == num-1) {
			direction[0] = maze_num-1;
			direction[1] = maze_num+1;
			direction[2] = maze_num-2*num;
			random_direction = rand() % 3; // 0~1
			chosen_maze_num = direction[random_direction];
		}

		// no north
		else if(random / num == 0) {
			direction[0] = maze_num;
			direction[1] = maze_num-1;
			direction[2] = maze_num+1;
			random_direction = rand() % 3; // 0~1
			chosen_maze_num = direction[random_direction];
		}

	// cycle check and update
	if(chosen_maze_num % 2 == 0) {
//		if(sets->ptr_arr[chosen_maze_num/2] < 0 || sets->ptr_arr[(chosen_maze_num+2*num)/2] < 0) continue;	
		
		if(sets->ptr_arr[chosen_maze_num/2] != 0 && sets->ptr_arr[(chosen_maze_num+2*num)/2] != 0 && sets->ptr_arr[chosen_maze_num/2] == sets->ptr_arr[(chosen_maze_num+2*num)/2] != 0)  continue;

		else {
			Union(sets, chosen_maze_num/2, (chosen_maze_num+2*num)/2);
			maze_print->ptr_arr[chosen_maze_num] = 0;
		}
	}
	else {
//		if(sets->ptr_arr[(chosen_maze_num-1)/2] < 0 || sets->ptr_arr[(chosen_maze_num+1)/2] < 0) continue;	
	
		if(sets->ptr_arr[(chosen_maze_num-1)/2] != 0 && sets->ptr_arr[(chosen_maze_num+1)/2] != 0 && sets->ptr_arr[(chosen_maze_num-1)/2] == sets->ptr_arr[(chosen_maze_num+1)/2] != 0)  continue;
		else {
			Union(sets, (chosen_maze_num-1)/2, (chosen_maze_num+1)/2);
			maze_print->ptr_arr[chosen_maze_num] = 0;
		}
	}

	// end condition
	if(	find(sets, 0) == find(sets, num*num-1)) return;
	}
}

void printMaze(DisjointSets *sets, int num) {
	int i = 0; int j = 0; int k = 0; int x = 0;

	for(i = 0; i < num*num; i++) {
		printf("sets->ptr_arr[%d]", i);
		printf("%d ", sets->ptr_arr[i]);
		printf("\n");
	}
	
	for(i = 0; i < 2*num*num; i++) {
		printf("maze->ptr_arr[%d]", i);
		printf("%d ", sets->ptr_arr[i]);
		printf("\n");
	}
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
