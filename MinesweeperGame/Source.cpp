// This project creates a minesweeper game with multiple difficulites 
// Created by Matthew Moran

#include <iostream>
#include <string>
#define MAXSIZE 15
using namespace std;

//POSSIBLE ADDITIONS:
//add a play again?
//add flags
//error prevention for initial input
//certain number of mines for each difficulty

void MakeMove(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]);

int diff;
int mines;

//make sure an input is not out of range or a spot that has already been selected
bool CheckValidInput(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	if (board[r][c] != '-') {
		return false;
	}
	return true;
}

//count the number of neighboring mines for a spot
int NumAdjMines(int r, int c, char hboard[MAXSIZE][MAXSIZE]) {
	int count = 0;
	/*
	8 possibilites:
	Northwest: [i-1][j-1]
	North: [i-1][j]
	Northeast: [i-1][j+1]
	East: [i][j+1]
	Southeast: [i+1][j+1]
	South: [i+1][j]
	Southwest: [i+1][j-1]
	West: [i][j-1]
	*/

	//NW
	if (hboard[r - 1][c - 1] == '*') {
		count++;
	}

	//N
	if (hboard[r - 1][c] == '*') {
		count++;
	}

	//NE
	if (hboard[r - 1][c + 1] == '*') {
		count++;
	}

	//E
	if (hboard[r][c + 1] == '*') {
		count++;
	}

	//SE
	if (hboard[r + 1][c + 1] == '*') {
		count++;
	}

	//S
	if (hboard[r + 1][c] == '*') {
		count++;
	}

	//SW
	if (hboard[r + 1][c - 1] == '*') {
		count++;
	}

	//W
	if (hboard[r][c - 1] == '*') {
		count++;
	}
	return count;
}

//print out board
void DisplayBoard(char board[MAXSIZE][MAXSIZE]) {
	cout << "   ";
	for (int i = 1; i <= diff; i++) {
		if (i < 10) {
			cout << i << "  ";
		}
		else {
			cout << i << " ";
		}
		
	}
	cout << endl;
	for (int i = 0; i < diff; i++) {
		if (i+1 < 10) {
			cout << i + 1 << "  ";
		}
		else {
			cout << i + 1 << " ";
		}
		for (int j = 0; j < diff; j++) {
			cout << board[i][j] << "  ";
		}
		cout << endl;
	}
}

//see if the board is completed (meaning the game is won)
void CheckWin(char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	bool same = true;
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			if (hboard[i][j] != '*') {
				if (board[i][j] != hboard[i][j]) {
					same = false;
				}
			}
		}
	}
	if (same == true) {
		cout << "You win!" << endl;
		DisplayBoard(board);
		exit(0);
	}
}

bool IsMine(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	if (hboard[r][c] != '*') {
		return false;
	}
	else {
		return true;
	}


}


//if a zero is shown, we want to show all of its neighbors
//if a number is shown and it has a zero as its neighbor, we want to show it
void ShowNeighbors(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	//make sure we are in the range of the board
	if (r < 0 || r >= diff || c < 0 || c >= diff) {
		return;
	}

	// Cell has already been revealed, no need to continue.
	if (board[r][c] != '-') {
		return;
	}

	// Reveal the current cell.
	board[r][c] = hboard[r][c];

	// Check if the revealed cell has a value of '0'.
	if (hboard[r][c] == '0') {
		// Recursively reveal neighboring cells.
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int newRow = r + i;
				int newCol = c + j;
				if (newRow >= 0 && newRow < diff && newCol >= 0 && newCol < diff) {
					ShowNeighbors(newRow, newCol, board, hboard);
				}
			}
		}
	}
	//if cell is not '0', check if there are any neighboring 0s
	if (hboard[r][c] != '0') {
		// Recursively reveal neighboring cells.
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int newRow = r + i;
				int newCol = c + j;
				if (newRow >= 0 && newRow < diff && newCol >= 0 && newCol < diff && hboard[newRow][newCol] == '0') {
					ShowNeighbors(newRow, newCol, board, hboard);
				}
			}
		}
	}
}


void GetDifficulty() {
	string diffSelect = "";
	cout << "Select Difficulty: \n (1) Easy \n (2) Medium \n (3) Hard \n (4) Exit\n";
	cin >> diffSelect;
	if (diffSelect == "1" || diffSelect == "Easy" || diffSelect == "easy") {
		diff = 9;
		mines = 15;
	}
	else if (diffSelect == "2" || diffSelect == "Medium" || diffSelect == "medium") {
		diff = 12;
		mines = 20;
	}
	else if (diffSelect == "3" || diffSelect == "Hard" || diffSelect == "hard") {
		diff = 15;
		mines = 25;
	}
	else if (diffSelect == "4" || diffSelect == "Exit" || diffSelect == "exit") {
		exit(0);
	}
	else {
		cout << "Not valid input. Try again.";
		GetDifficulty();
	}
}

//prompt for the user to input their move
void MovePrompt(char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	int row, col;
	cout << "Make a move:" << endl;
	cout << "Row: ";
	cin >> row;
	cout << "Column: ";
	cin >> col;

	//rows and cols adjusted to reflect how to board is displayed
	row = row - 1;
	col = col - 1;
	MakeMove(row, col, board, hboard);
}

//makes the move and changes the board using the input from the user
void MakeMove(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	
	if (CheckValidInput(r, c, board, hboard) == false) {
		cout << "Not a valid input. Try again" << endl;
		MovePrompt(board, hboard);
	}
	else {
		if (IsMine(r, c, board, hboard) == false) {
			if (hboard[r][c] == '0') {
				ShowNeighbors(r, c, board, hboard);
			}
			else {
				board[r][c] = hboard[r][c];
			}
			CheckWin(board, hboard);
			DisplayBoard(board);
			MovePrompt(board, hboard);
		}
		else {
			cout << "You lost!" << endl;
			DisplayBoard(hboard);
			exit(0);
		}
	}

}

//place mines in the empty hidden board
void PlaceMines(int r, int c, int remMines, char hboard[MAXSIZE][MAXSIZE]) {
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			if (rand() % mines + 1 == 1 &&
				(i != r && j != c) &&
				(i - 1 != r && j - 1 != c) &&
				(i - 1 != r && j != c) &&
				(i - 1 != r && j + 1 != c) &&
				(i != r && j + 1 != c) &&
				(i + 1 != r && j + 1 != c) &&
				(i + 1 != r && j != c) &&
				(i + 1 != r && j - 1 != c) &&
				(i != r && j - 1 != c) && 
				hboard[i][j] != '*')
			{
				hboard[i][j] = '*';
				remMines--;

				//no more mines to place
				if (remMines == 0) {
					return;
				}
			}
		}
	}
	//if we still have mines to place, run again
	PlaceMines(r, c, remMines, hboard);
}

//main function
void CreateTable() {

	//makes the randomization different each run
	srand(time(0));

	int startRow, startCol;
	char hiddenBoard[MAXSIZE][MAXSIZE], board[MAXSIZE][MAXSIZE];
	cout << "MINESWEEPER" << endl;
	cout << "Moves are made by entering a row and a column in the table." << endl;
	GetDifficulty();

	//make blank board
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			board[i][j] = '-';
		}
	}
	DisplayBoard(board);

	cout << "Select a starting position: " << endl;
	cout << "Row: ";
	cin >> startRow;
	cout << "Column: ";
	cin >> startCol;
	startRow = startRow - 1;
	startCol = startCol - 1;

	PlaceMines(startRow, startCol, mines, hiddenBoard);

	//fill the hidden board with the Adjacent mines of each cell
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			if (hiddenBoard[i][j] != '*') {
				//+48 is used to adjust from ASCII values
				hiddenBoard[i][j] = char(NumAdjMines(i, j, hiddenBoard) + 48);
			}
		}
	}
	ShowNeighbors(startRow, startCol, board, hiddenBoard);
	DisplayBoard(board);
	MovePrompt(board, hiddenBoard);
}


int main() {
	CreateTable();
}