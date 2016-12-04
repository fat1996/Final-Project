#include <iostream>
#include <string>
#include <vector>
#include "grid.h"
#include "block.h"
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

using namespace std;

grid::~grid(){
	for(int i=0;i<boardheight;i++) {
		delete [] board[i];
	}
	delete [] board;
	delete level;
	currentBlock->deleteBlock();
	delete currentBlock;
	delete nextBlock;
}

map<int, int> grid::returnRows(){
	return emptyRows;
}

string** grid::returnBoard(){
	return board;
}

vector<history*> &grid::returnGridList(){
	return GridList;
}

bool &grid::returnGameOver(){
	return gameOver;
}

int &grid::returnCurScore(){
	return currentScore;
}


void grid::SetBoard(int level_num, string scriptfile) {   //this sets up the initial configuration of the board.
	gameOver=false;
	currentScore=0;
	
	board = new string*[boardheight];
	for(int i=0; i<boardheight ; i++) {
		board[i] = new string[boardwidth];
		for(int j = 0; j<boardwidth ; j++) {
			board[i][j]=" ";
		}
	int rowIndex = i;
	emptyRows[rowIndex]=0; //0 means empty. The entire row is empty.	
	}
	if (level_num == 0) {
		level = new Level0(scriptfile);
	} else if (level_num == 1) {
		level = new Level1();
	} else if (level_num == 2) {
		level = new Level2();
	} else {
		level = new Level3();
	}
	currentBlock = level->getNextBlock();
	currentBlock->initialize(this->board, level_num);
	nextBlock = level->getNextBlock();
}

void grid::drawNextBlock() {
	char type = nextBlock->getType();
	cout << "\nNext:" << endl;
	if (type == 'J') {
		cout << "J\nJJJ" << endl;
	} else if (type == 'I') {
		cout << "IIII" << endl;
	} else if (type == 'L') {
		cout << "  L\nLLL" << endl;
	} else if (type == 'O') {
		cout << "OO\nOO" << endl;
	} else if (type == 'Z') {
		cout << "ZZ \n ZZ" << endl;
	} else if (type == 'S') {
		cout << " SS\nSS " << endl;
	} else {
		cout << "TTT\n T" << endl;
	}
	cout << "\n" << endl;
}

void grid::DrawBoard() {
	cout<<"---------------"<<endl;
	for (int i=0 ; i<boardheight ;i++) {
		for (int j=0; j<boardwidth; j++){
			cout<<board[i][j];
		}
	cout<<endl;
	}
	cout<<"---------------"<<endl;
	drawNextBlock();
}

block* grid::getCurrentBlock() {
	return this->currentBlock;
}

block* grid::getNextBlock() {
	this->currentBlock = this->nextBlock;
	currentBlock->initialize(this->board, level->getLevel());
	this->nextBlock = this->level->getNextBlock();
	return this->nextBlock;
}

// Main already handles case where curLevel is 4
void grid::levelUp() {
	int curLevel = level->getLevel();
	delete level;
	if (curLevel == 0) {
		level = new Level1();
	} else if (curLevel == 1) {
		level = new Level2();
	} else if (curLevel == 2) {
		level = new Level3();
	} else {
		level = new Level4();
	}
}

// Main already handles case where curLevel is 0
void grid::levelDown(string scriptfile) {
	int curLevel = level->getLevel();
	delete level;
	if (curLevel == 1) {
		level = new Level0(scriptfile);
	} else if (curLevel == 2) {
		level = new Level1();
	} else if (curLevel == 3) {
		level = new Level2();
	} else {
		level = new Level3();
	}
}
