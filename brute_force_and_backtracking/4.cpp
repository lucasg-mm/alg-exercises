#include<cstdio>
#define MAX_SIZE 10  // maze's MAXIMUM size
#define RAT 2  // used for marking places the rat already visited

using namespace std;

// global variables
int maze[MAX_SIZE][MAX_SIZE];  // the maze itself
int maze_size;  // the size of the maze
int moves[4][2] = { 1,  0,  // possible moves of the rat
				   -1,  0,
					0,  1,
					0, -1 };

// tells if a rat's position in the maze is valid
bool is_valid(int line_position, int column_position){
	// valid
	if(line_position < maze_size && column_position < maze_size && line_position >= 0 && column_position >= 0 && maze[line_position][column_position] == 0 && maze[line_position][column_position] != RAT){
		return true;
	}
	else{  // not valid
		return false;
	}
}					

// counts possible paths through backtracking
void count_paths(int line_position, int column_position, int* num_paths){
	int i;
	int new_line_position;
	int new_column_position;

	if((line_position == maze_size - 1) && (column_position == maze_size - 1)){
		// found the cheese!
		(*num_paths)++;
	}
	else{
		for(i = 0; i < 4; i++){
			// tests a new rat's position
			new_line_position = line_position + moves[i][0];
			new_column_position = column_position + moves[i][1];
			if(is_valid(new_line_position, new_column_position)){  // if the position is valid...
				maze[new_line_position][new_column_position] = RAT;  // marks that the rat already got there
				count_paths(new_line_position, new_column_position, num_paths);  // backtracking recursion
				maze[new_line_position][new_column_position] = 0;  // undo the marking
			}
		}
	}
}

int main(){
	int i;
	int j;
	int num_paths;  // holds the number of paths

	// gets the maze size
	while(scanf("%d", &maze_size) != EOF){  // the problem states the program must read from a file
		num_paths = 0;  // initializes number of paths for each test case

		// gets the maze itself
		for(i = 0; i < maze_size; i++){
			for(j = 0; j < maze_size; j++){
				scanf("%d", &maze[i][j]);
			}
		}

		// mark rat's initial position (0, 0) in this case
		maze[0][0] = RAT;

		// backtracks and prints the answer
		count_paths(0, 0, &num_paths);
		printf("%d", num_paths);
	}

	// bye!
	return 0;
}