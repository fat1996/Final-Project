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

void grid::cleanUp() {
	int size = GridList.size();
	int z = 0;
        while(z < size) {
                history *h=GridList[z];
 	        delete h;
		GridList.erase(GridList.begin()+z);
		size = GridList.size();
	}
	for(int i=0;i<boardheight;i++) {
		delete [] board[i];
	}
	delete [] board;
	delete level;
	delete currentBlock;
	delete nextBlock;
}

	
grid::~grid(){
	int size = GridList.size();
	int z = 0;
	while(z < size) {
		history *h=GridList[z];
	        delete h;
	        GridList.erase(GridList.begin()+z);
		size = GridList.size();
	}

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

int &grid::returnCurScore(){
	return currentScore;
}


void grid::SetBoard(int level_num, string scriptfile, bool& gameOver) {   //this sets up the initial configuration of the board.
//	gameOver=false;
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
	currentBlock->initialize(this->board, level_num, gameOver);
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

void grid::DrawBoard(int l, int hiScore) {
	cout<<"Level:	"<<l<<endl;
	cout<<"Score:	"<<currentScore<<endl;
	cout<<"Hi Score:"<<hiScore<<endl;
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

block* grid::getNextBlock(bool &gameOver) {
	this->currentBlock = this->nextBlock;
	//bool gameOver = 
	currentBlock->initialize(this->board, level->getLevel(), gameOver);
/*	if(gameOver==false){  //gameover. stop.
		cout << "Gameover print" << endl;
		return nullptr;
	}
	else{ */
		this->nextBlock = this->level->getNextBlock();
		return this->nextBlock;
}

block* grid::returnNextBlock() {
	return this->nextBlock;
}

void grid::setCurrentBlock(block* b, bool& gameOver) {
	currentBlock = b;
	currentBlock->initialize(this->board, level->getLevel(), gameOver);
}

void grid::setNextBlock(block* b) {
	nextBlock = b;
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
