// This project creates a minesweeper game with multiple difficulites 
// Created by Matthew Moran

#include <iostream>
#include <string>
#define MAXSIZE 10
using namespace std;

//NOTE: once done, add protection so the user does not give invalid input

void MakeMove(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]);

//this is temporary
int diff = 9;

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


void DisplayBoard(char board[MAXSIZE][MAXSIZE]) {
	cout << "  ";
	for (int i = 1; i <= diff; i++) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < diff; i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < diff; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

bool IsValid(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	if (hboard[r][c] != '*') {
		return true;
	}
	else {
		return false;
	}


}

void ShowNeighbors(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	//note: all instances with 8 are temporary and need to be changed so it can vary based on the grid size
	if (r > 0 && c > 0) {
		if (board[r - 1][c - 1] != '0' && hboard[r - 1][c - 1] != '*') {
			board[r - 1][c - 1] = hboard[r - 1][c - 1];
			if (hboard[r - 1][c - 1] == '0') {
				ShowNeighbors(r - 1, c - 1, board, hboard);
			}
		}
	}

	if (r > 0) {
		if (board[r - 1][c] != '0' && hboard[r - 1][c] != '*') {
			board[r - 1][c] = hboard[r - 1][c];
			if (hboard[r - 1][c] == '0') {
				ShowNeighbors(r - 1, c, board, hboard);
			}
		}
	}

	if (r > 0 && c < 8) {
		if (board[r - 1][c + 1] != '0' && hboard[r - 1][c + 1] != '*') {
			board[r - 1][c + 1] = hboard[r - 1][c + 1];
			if (hboard[r - 1][c + 1] == '0') {
				ShowNeighbors(r - 1, c + 1, board, hboard);
			}
		}

	}
	
	if (c < 8) {
		if (board[r][c + 1] != '0' && hboard[r][c + 1] != '*') {
			board[r][c + 1] = hboard[r][c + 1];
			if (hboard[r][c + 1] == '0') {
				ShowNeighbors(r, c + 1, board, hboard);
			}
		}
	}

	if (r < 8 && c < 8) {
		if (board[r + 1][c + 1] != '0' && hboard[r + 1][c + 1] != '*') {
			board[r + 1][c + 1] = hboard[r + 1][c + 1];
			if (hboard[r + 1][c + 1] == '0') {
				ShowNeighbors(r + 1, c + 1, board, hboard);
			}
		}
	}

	if (r < 8) {
		if (board[r + 1][c] != '0' && hboard[r + 1][c] != '*') {
			board[r + 1][c] = hboard[r + 1][c];
			if (hboard[r + 1][c] == '0') {
				ShowNeighbors(r + 1, c, board, hboard);
			}
		}
	}

	if (r < 8 && c > 0) {
		if (board[r + 1][c - 1] != '0' && hboard[r + 1][c - 1] != '*') {
			board[r + 1][c - 1] = hboard[r + 1][c - 1];
			if (hboard[r + 1][c - 1] == '0') {
				ShowNeighbors(r + 1, c - 1, board, hboard);
			}
		}
	}

	if (c > 0) {
		if (board[r][c - 1] != '0' && hboard[r][c - 1] != '*') {
			board[r][c - 1] = hboard[r][c - 1];
			if (hboard[r][c - 1] == '0') {
				ShowNeighbors(r, c - 1, board, hboard);
			}
		}
	}
}


int GetDifficulty() {
	string diff = "";
	cout << "Select Difficulty: \n (1) Easy \n (2) Medium \n (3) Hard \n (4) Exit";
	cin >> diff;
	if (diff == "1" || diff == "Easy" || diff == "easy") {
		return 9;
	}
	else if (diff == "2" || diff == "Medium" || diff == "medium") {
		return 12;
	}
	else if (diff == "3" || diff == "Hard" || diff == "hard") {
		return 15;
	}
	else if (diff == "4" || diff == "Exit" || diff == "exit") {
		exit(0);
	}
	else {
		cout << "Not valid input. Try again.";
		GetDifficulty();
	}
	return 0;
}

void MovePrompt(char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	int row, col;
	cout << "Make a move:" << endl;
	cout << "Row: ";
	cin >> row;
	cout << "Column: ";
	cin >> col;
	row = row - 1;
	col = col - 1;
	MakeMove(row, col, board, hboard);
}

void MakeMove(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	if (IsValid(r, c, board, hboard) == true) {
		board[r][c] = hboard[r][c];
		if (board[r][c] == 0) {
			ShowNeighbors(r, c, board, hboard);
		}
		DisplayBoard(board);
		MovePrompt(board, hboard);
	}
	else {
		cout << "You lost!" << endl;
		DisplayBoard(hboard);
		//cout << "Play again?" << endl;
		//cin >> response;
		//if (response == "Y" || response == "y" || response == "yes" || response == "Yes") {
		//	CreateTable();
		//}
	}

}

void CreateTable() {
	int startRow, startCol;
	char hiddenBoard[MAXSIZE][MAXSIZE], board[MAXSIZE][MAXSIZE];
	cout << "MINESWEEPER" << endl;
	cout << "Moves are made by entering a row and a column in the table." << endl;
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			board[i][j] = '-';
		}
	}
	DisplayBoard(board);
	//still need to factor in the difficulty function
	cout << "Select a starting position: " << endl;
	cout << "Row: ";
	cin >> startRow;
	cout << "Column: ";
	cin >> startCol;
	startRow = startRow - 1;
	startCol = startCol - 1;
	
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			
			//place mines randomly
			// the starting position should have no adj mines

			if (rand() % 3 == 0 &&
				(i != startRow && j != startCol) &&
				(i - 1 != startRow && j - 1 != startCol) &&
				(i - 1 != startRow && j != startCol) &&
				(i - 1 != startRow && j + 1 != startCol) &&
				(i != startRow && j + 1 != startCol) &&
				(i + 1 != startRow && j + 1 != startCol) &&
				(i + 1 != startRow && j != startCol) &&
				(i + 1 != startRow && j - 1 != startCol) &&
				(i != startRow && j - 1 != startCol)) {
				hiddenBoard[i][j] = '*';
			}
		}
	}
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			if (hiddenBoard[i][j] != '*') {
				hiddenBoard[i][j] = char(NumAdjMines(i, j, hiddenBoard) + 48);
			}
		}
	}
	board[startRow][startCol] = char(NumAdjMines(startRow, startCol, hiddenBoard) + 48);
	ShowNeighbors(startRow, startCol, board, hiddenBoard);
	DisplayBoard(board);
	MovePrompt(board, hiddenBoard);
}


int main() {
	CreateTable();
}