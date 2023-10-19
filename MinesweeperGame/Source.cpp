// This project creates a minesweeper game with multiple difficulites 
// Created by Matthew Moran

#include <iostream>
#include <string>

#define MAXSIZE 15
using namespace std;

//NOTE: once done, add protection so the user does not give invalid input

//maybe make a function CheckValidInput() that makes sure whatever a user inputs is valid
//bool CheckValidInput(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {}

void MakeMove(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]);

int diff;


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

bool IsValid(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	if (hboard[r][c] != '*') {
		return true;
	}
	else {
		return false;
	}


}

void ShowNeighbors(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
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

	if (r > 0 && c < diff-1) {
		if (board[r - 1][c + 1] != '0' && hboard[r - 1][c + 1] != '*') {
			board[r - 1][c + 1] = hboard[r - 1][c + 1];
			if (hboard[r - 1][c + 1] == '0') {
				ShowNeighbors(r - 1, c + 1, board, hboard);
			}
		}

	}
	
	if (c < diff - 1) {
		if (board[r][c + 1] != '0' && hboard[r][c + 1] != '*') {
			board[r][c + 1] = hboard[r][c + 1];
			if (hboard[r][c + 1] == '0') {
				ShowNeighbors(r, c + 1, board, hboard);
			}
		}
	}

	if (r < diff - 1 && c < diff - 1) {
		if (board[r + 1][c + 1] != '0' && hboard[r + 1][c + 1] != '*') {
			board[r + 1][c + 1] = hboard[r + 1][c + 1];
			if (hboard[r + 1][c + 1] == '0') {
				ShowNeighbors(r + 1, c + 1, board, hboard);
			}
		}
	}

	if (r < diff - 1) {
		if (board[r + 1][c] != '0' && hboard[r + 1][c] != '*') {
			board[r + 1][c] = hboard[r + 1][c];
			if (hboard[r + 1][c] == '0') {
				ShowNeighbors(r + 1, c, board, hboard);
			}
		}
	}

	if (r < diff - 1 && c > 0) {
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


void GetDifficulty() {
	string diffSelect = "";
	cout << "Select Difficulty: \n (1) Easy \n (2) Medium \n (3) Hard \n (4) Exit\n";
	cin >> diffSelect;
	if (diffSelect == "1" || diffSelect == "Easy" || diffSelect == "easy") {
		diff = 9;
	}
	else if (diffSelect == "2" || diffSelect == "Medium" || diffSelect == "medium") {
		diff = 12;
	}
	else if (diffSelect == "3" || diffSelect == "Hard" || diffSelect == "hard") {
		diff = 15;
	}
	else if (diffSelect == "4" || diffSelect == "Exit" || diffSelect == "exit") {
		exit(0);
	}
	else {
		cout << "Not valid input. Try again.";
		GetDifficulty();
	}
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
		CheckWin(board, hboard);
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
	srand(time(0));
	int startRow, startCol;
	char hiddenBoard[MAXSIZE][MAXSIZE], board[MAXSIZE][MAXSIZE];
	cout << "MINESWEEPER" << endl;
	cout << "Moves are made by entering a row and a column in the table." << endl;
	GetDifficulty();
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