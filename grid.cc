#include <iostream>
#include <string>
#include <vector>
#include "grid.h"
#include "block.h"
#include "level.h"
#include "level0.h"

using namespace std;

grid::~grid(){
	for(int i=0;i<boardheight;i++) {
		delete [] board[i];
	}
	delete [] board;
	delete level;
	delete currentBlock;
	delete nextBlock;
	int size = activeBlocks.size();
	for (int i = 0; i < size ; i++) {
		delete (activeBlocks[i]);
		} 
	activeBlocks.clear();
}

map<string, int> grid::returnRows(){
	return emptyRows;
}

string** grid::returnBoard(){
	return board;
}

void grid::SetBoard(int level_num, string scriptfile) {   //this sets up the initial configuration of the board.
	board = new string*[boardheight];
	for(int i=0; i<boardheight ; i++) {
		board[i] = new string[boardwidth];
		for(int j = 0; j<boardwidth ; j++) {
			board[i][j]=" ";
		}
	string rowIndex = to_string(i);
	emptyRows[rowIndex]=0; //0 means empty. The entire row is empty.	
	}
	level = new Level0(scriptfile);
	currentBlock = level->getNextBlock();
	currentBlock->initialize(this->board);
	activeBlocks.push_back(currentBlock);
	nextBlock = level->getNextBlock();
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
}

block* grid::getCurrentBlock() {
	return this->currentBlock;
}

block* grid::getNextBlock() {
	this->currentBlock = this->nextBlock;
	currentBlock->initialize(this->board);
	activeBlocks.push_back(currentBlock);
	this->nextBlock = this->level->getNextBlock();
	return this->nextBlock;
}
