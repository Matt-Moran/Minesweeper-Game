// This project creates a minesweeper game with multiple difficulites 
// Created by Matthew Moran

// Packages
#include <iostream>
#include <string>
using namespace std;

int row, col;
int const diff = GetDifficulty();
string hiddenBoard[diff][diff];
string board[diff][diff];


void CreateTable() {
	int startRow, startCol;
	cout << "Select a starting position: " << endl;
	cout << "Row: " << endl;
	cin >> startRow;
	cout << "Column: " << endl;
	cin >> startCol;
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			if (rand() % 2 == 0 && i != startRow and j != startCol) {
				hiddenBoard[i][j] = '*';
			}
		}
	}
	board = hiddenBoard;
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			hiddenBoard[i][j] = NumAdjMines(i, j);
		}
	}
	DisplayBoard();
}

void MakeMove(int r, int c) {}

int GetDifficulty() {
	string diff = "";
	cout << "Select Difficulty: \n (1) Easy \n (2) Medium \n (3) Hard \n (4) Exit";
	cin >> diff;
	if (diff == "1" || diff == "Easy" || diff == "easy") {
		row = 9;
		col = 9;
		return 9;
	}
	else if (diff == "2" || diff == "Medium" || diff == "medium") {
		row = 20;
		col = 20;
		return 20;
	}
	else if (diff == "3" || diff == "Hard" || diff == "hard") {
		row = 50;
		col = 50;
		return 50;
	}
	else if (diff == "4" || diff == "Exit" || diff == "exit") {
		exit(0);
	}
	else {
		cout << "Not valid input. Try again.";
		GetDifficulty();
	}
}

int DisplayBoard() {
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			cout << board[i][j];
		}
	}
}

int DisplayHiddenBoard() {
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			cout << hiddenBoard[i][j];
		}
	}
}

bool IsValid(int r, int c) {}

int NumAdjMines(int r, int c) {
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
	if (hiddenBoard[r-1][c-1] == '*') {
		count++;
	}

	//N
	if (hiddenBoard[r-1][c] == '*') {
		count++;
	}

	//NE
	if (hiddenBoard[r-1][c+1] == '*') {
		count++;
	}

	//E
	if (hiddenBoard[r][c+1] == '*') {
		count++;
	}

	//SE
	if (hiddenBoard[r+1][c+1] == '*') {
		count++;
	}

	//S
	if (hiddenBoard[r+1][c] == '*') {
		count++;
	}

	//SW
	if (hiddenBoard[r+1][c-1] == '*') {
		count++;
	}

	//W
	if (hiddenBoard[r][c-1] == '*') {
		count++;
	}
	return count; 
}


int main() {

}