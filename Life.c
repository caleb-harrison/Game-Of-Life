#include <stdio.h>
#include <unistd.h>

// --------------------------------------------------------------------

#define BOARD_SIZE 36
#define MAX_STEPS 1000

// --------------------------------------------------------------------

int countNeighbors(int board[BOARD_SIZE][BOARD_SIZE], int row, int col) {

	int numNeighbors = 0;
  
	for (int row_offset = -1; row_offset <= 1; row_offset++) {
		for (int col_offset = -1; col_offset <= 1; col_offset++) {
			int i = row + row_offset;
			int j = col + col_offset;
			if ((i >= 0) && (i < BOARD_SIZE) &&
				(j >= 0) && (j < BOARD_SIZE)) {
				if (board[i][j] == 1) {
					numNeighbors += 1;
				}
			}
		}
	}

	// makes sure we dont count original
	numNeighbors -= board[row][col];

	// amount of neighbors
	return numNeighbors;

}

// --------------------------------------------------------------------

void copyBoardToBoard(int srcBoard[BOARD_SIZE][BOARD_SIZE], int dstBoard[BOARD_SIZE][BOARD_SIZE]) {
 
	// for each row
	for (int i = 0; i < BOARD_SIZE; i++) {
		// for each column
		for (int j = 0; j < BOARD_SIZE; j++) {
			dstBoard[i][j] = srcBoard[i][j];
		}
	}
}

// --------------------------------------------------------------------

void changeBoard(int board[BOARD_SIZE][BOARD_SIZE]) {

	int oldBoard[BOARD_SIZE][BOARD_SIZE];
	copyBoardToBoard(board, oldBoard);

	// iterate over oldBoard, mutating board as we go
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			int oldValue = oldBoard[i][j];
			int numNeighbors = countNeighbors(oldBoard, i, j);

			// living cells die if less than 2 neighbors
			// living cells die if more than 3 neighbors
			if ((oldValue == 1) && ((numNeighbors < 2) || (numNeighbors > 3))) {
				board[i][j] = 0;

			// dead cells that have 3 neighbors become alive
	  		} else if ((oldValue == 0) && (numNeighbors == 3)) {
				board[i][j] = 1;
			}

			// otherwise, do nothing
	}
  }  
}

// --------------------------------------------------------------------

void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {

	// for each row
	printf("                                             ");
	for (int i = 0; i < BOARD_SIZE; i++) {
		// for each column
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == 1) {
				printf("|X");
			} else {
				printf("| ");
			}
		}
		printf("|\n                                             ");
	}
	printf("\n");
}

// --------------------------------------------------------------------

void gameOfLife() {

	int board[BOARD_SIZE][BOARD_SIZE] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
 {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

	printBoard(board);

	for (int i = 0; i < MAX_STEPS; i++) {
		usleep(50000);
		changeBoard(board);
		printBoard(board);
	}
}

// --------------------------------------------------------------------

int main(int argc, char *argv[]) {  
	printf("Game of Life!\n\n");
	gameOfLife();
	return 0;
}

// --------------------------------------------------------------------
