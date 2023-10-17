// This project creates a minesweeper game with multiple difficulites 
// Created by Matthew Moran

#include <iostream>
#include <string>
#define MAXSIZE 15
using namespace std;

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
	if (NumAdjMines(r, c, hboard) == 0) {
		return true;
	}
	else {
		return false;
	}


}

void ShowZeros(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	//if you make a valid click, the adj boxes with 0 adj mines should also be shown
	//need to check all 8 cases
	if (hboard[r - 1][c - 1] == '0') {
		board[r - 1][c - 1] = '0';
	}
	if (hboard[r-1][c] == '0') {
		board[r-1][c] = '0';
	}
	if (hboard[r-1][c+1] == '0') {
		board[r-1][c+1] = '0';
	}
	if (hboard[r][c+1] == '0') {
		board[r][c+1] = '0';
	}
	if (hboard[r+1][c+1] == '0') {
		board[r+1][c+1] = '0';
	}
	if (hboard[r+1][c] == '0') {
		board[r+1][c] = '0';
	}
	if (hboard[r+1][c-1] == '0') {
		board[r+1][c-1] = '0';
	}
	if (hboard[r][c-1] == '0') {
		board[r][c-1] = '0';
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
	cout << "Make a move:";
	cout << "Row: ";
	cin >> row;
	cout << "Column: ";
	cin >> col;
	MakeMove(row, col, board, hboard);
}

void MakeMove(int r, int c, char board[MAXSIZE][MAXSIZE], char hboard[MAXSIZE][MAXSIZE]) {
	if (IsValid(r, c, board, hboard) == true) {
		board[r][c] = hboard[r][c];
		ShowZeros(r, c, board, hboard);
		DisplayBoard(board);
		MovePrompt(board, hboard);
	}
	else {
		string response = "";
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
	//still need to factor in the difficulty function
	cout << "Select a starting position: " << endl;
	cout << "Row: ";
	cin >> startRow;
	cout << "Column: ";
	cin >> startCol;
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			board[i][j] = '-';
		}
	}
	DisplayBoard(board);
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
				board[i][j] = '*';
			}
		}
	}
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			hiddenBoard[i][j] = char(NumAdjMines(i, j, hiddenBoard));
		}
	}
	DisplayBoard(board);
	cout << "Moves are made by entering a row and a column in the table." << endl;
	MovePrompt(board, hiddenBoard);
}


int main() {
	CreateTable();
}