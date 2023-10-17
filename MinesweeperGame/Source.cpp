// This project creates a minesweeper game with multiple difficulites 
// Created by Matthew Moran

// Packages
#include <iostream>
#include <string>
using namespace std;

int const diff = GetDifficulty();
string hiddenBoard[diff][diff];
string board[diff][diff];


void CreateTable() {
	int startRow, startCol;
	cout << "MINESWEEPER" << endl;
	cout << "Select a starting position: " << endl;
	cout << "Row: " << endl;
	cin >> startRow;
	cout << "Column: " << endl;
	cin >> startCol;
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {

			// the starting position should have no adj mines

			if (rand() % 3 == 0 && 
				(i != startRow && j != startCol) &&
				(i-1 != startRow && j-1 != startCol)&&
				(i-1 != startRow && j != startCol)&&
				(i-1 != startRow && j+1 != startCol)&&
				(i != startRow && j+1 != startCol)&&
				(i+1 != startRow && j+1 != startCol)&&
				(i+1 != startRow && j != startCol)&&
				(i+1 != startRow && j-1 != startCol)&&
				(i != startRow && j-1 != startCol)) {
				hiddenBoard[i][j] = '*';
			}
		}
	}
	board = hiddenBoard;
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < diff; j++) {
			hiddenBoard[i][j] = to_string(NumAdjMines(i, j));
		}
	}
	cout << "Moves are made by entering a row and a column in the table." << endl;
	DisplayBoard();
	MovePrompt();
}

void ShowZeros(int r, int c) {
	//if you make a valid click, the adj boxes with 0 adj mines should also be shown
	//need to check all 8 cases
	if (hiddenBoard[r - 1][c - 1] == '0') {
		board[r - 1][c - 1] = '0';
	}
	if (hiddenBoard[r-1][c] == '0') {
		board[r-1][c] = '0';
	}
	if (hiddenBoard[r-1][c+1] == '0') {
		board[r-1][c+1] = '0';
	}
	if (hiddenBoard[r][c+1] == '0') {
		board[r][c+1] = '0';
	}
	if (hiddenBoard[r+1][c+1] == '0') {
		board[r+1][c+1] = '0';
	}
	if (hiddenBoard[r+1][c] == '0') {
		board[r+1][c] = '0';
	}
	if (hiddenBoard[r+1][c-1] == '0') {
		board[r+1][c-1] = '0';
	}
	if (hiddenBoard[r][c-1] == '0') {
		board[r][c-1] = '0';
	}
}

void MovePrompt() {
	int row, col;
	cout << "Make a move:";
	cout << "Row: " << endl;
	cin >> row;
	cout << "Column: " << endl;
	cin >> col;
	MakeMove(row, col);
}

void MakeMove(int r, int c) {
	if (IsValid(r, c) == true) {
		board[r][c] == hiddenBoard[r][c];
		ShowZeros(r,c);
		DisplayBoard();
		MovePrompt();
	}
	else {
		string response = "";
		cout << "You lost!" << endl;
		DisplayHiddenBoard();
		cout << "Play again?" << endl;
		cin >> response;
		if (response == "Y" || response == "y" || response == "yes" || response == "Yes") {
			CreateTable();
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
		return 20;
	}
	else if (diff == "3" || diff == "Hard" || diff == "hard") {
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

bool IsValid(int r, int c) {
	if (NumAdjMines(r, c) == 0) {
		return true;
	}
	else {
		return false;
	}


}

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
	CreateTable();
}