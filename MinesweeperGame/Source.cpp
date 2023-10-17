// This project creates a minesweeper game with multiple difficulites 
// Created by Matthew Moran

// Packages
#include <iostream>
#include <string>
using namespace std;

//Variables
int row, col;
int board;
int hiddenBoard;

void CreateTable() {}

void MakeMove(int r, int c) {}

void GetDifficulty() {
	string diff = "";
	cout << "Select Difficulty: \n (1) Easy \n (2) Medium \n (3) Hard \n (4) Exit";
	cin >> diff;
	if (diff == "1" || diff == "Easy" || diff == "easy") {
		row = 9;
		col = 9;
	}
	else if (diff == "2" || diff == "Medium" || diff == "medium") {
		row = 20;
		col = 20;
	}
	else if (diff == "3" || diff == "Hard" || diff == "hard") {
		row = 50;
		col = 50;
	}
	else if (diff == "4" || diff == "Exit" || diff == "exit") {
		exit(0);
	}
	else {
		cout << "Not valid input. Try again.";
		GetDifficulty();
	}
}

int DisplayBoard() {}

int DisplayHiddenBoard() {}

bool IsValid(int r, int c) {}

int NumAdjMines(int r, int c) {}


int main() {


}