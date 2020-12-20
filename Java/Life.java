public class Life {

// --------------------------------------------------------------------

	public int BOARD_SIZE = 5;
	public int MAX_STEPS = 5;

//--------------------------------------------------------------------
	
	int countNeighbors(int[][] board, int row, int col) {

		int numNeighbors = 0;

		for (int row_offset = -1; row_offset <= 1; row_offset++) {
			for (int col_offset = -1; col_offset <= 1; col_offset++) {
				int i = row + row_offset;
				int j = col + col_offset;
				if((i >= 0) && (i < BOARD_SIZE) &&
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

//--------------------------------------------------------------------
	
	void copyBoardToBoard(int[][] sourceBoard, int[][] destBoard) {

		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				destBoard[i][j] = sourceBoard[i][j];
			}
		}

	}

//--------------------------------------------------------------------
	
	void changeBoard(int[][] board) {

		int[][] oldBoard = new int[BOARD_SIZE][BOARD_SIZE];
		copyBoardToBoard(board, oldBoard);

		// iterate over oldBoard, mutating board as we go
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				int oldValue = oldBoard[i][j];
				int numNeighbors = countNeighbors(oldBoard, i, j);

				// living cells die if less than 2 neighbors
				// living cells die if more than 3 neighbors
				if((oldValue == 1) && ((numNeighbors < 2) || (numNeighbors > 3))){
					board[i][j] = 0;
				} 
				// dead cells that have 3 neighbors become alive
				if((oldValue == 0) && (numNeighbors == 3)) {
					board[i][j] = 1;
				}
				// otherwise there is no change (dead or alive)
			}
		}

	}

//--------------------------------------------------------------------
	
	void printBoard(int[][] board) {
		// for each row
		for (int i = 0; i < BOARD_SIZE; i++) {
			// for each column
			for (int j = 0; j < BOARD_SIZE; j++) {
				if(board[i][j] == 1) {
					System.out.print("X|");
				} else {
					System.out.print(".|");
				}
			}
			System.out.print("\n");
		}
		System.out.print("\n");

	}

//--------------------------------------------------------------------
	
	void gameOfLife() {
		System.out.print("Game of life!\n\n");
		int[][] board = {{0,0,1,0,0},
					     {0,1,0,0,1},
					     {0,0,0,0,1},
					     {0,1,1,0,0},
					     {0,0,1,0,0}};
		/*
		int[][] board = {{0,1,0,0,1}, // infinite board
					     {0,0,0,0,0},
					     {0,1,0,1,0},
					     {0,0,0,1,0},
					     {1,0,0,0,0}};
		*/
		printBoard(board);

		for (int i = 0; i < MAX_STEPS; i++) {
			changeBoard(board);
			printBoard(board);
		}

	}

//--------------------------------------------------------------------
	
	public static void main(String[] args) {
		Life game1 = new Life();
		game1.gameOfLife();
	}
}

//--------------------------------------------------------------------