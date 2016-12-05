#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "coordinate.h"
#include "starblock.h"
#include "block.h"
#include "history.h"

using namespace std;

// Constructor that sets type
StarBlock::StarBlock() : block{'*'} {}

// Initializer
void StarBlock::initialize(string** board, int level_num, bool &gameOver) {
	level = level_num;
	if(board[3][6] != " ") {
		// Middle of first row is full
		gameOver = true;
	}
	else {
		blockCoord[0]=new Coordinate;
		blockCoord[0]->setCoord(3, 6);

		// Set other coordinates as 0 default: NEVER check/use them
		blockCoord[1]=new Coordinate;
		blockCoord[1]->setCoord(0, 0);

		blockCoord[2]=new Coordinate;
		blockCoord[2]->setCoord(0, 0);

		blockCoord[3]=new Coordinate;
		blockCoord[3]->setCoord(0, 0);
	}
}

// Default destructor
StarBlock::~StarBlock() {}

// Needed to ensure class is not abstract
void StarBlock::clockwise(string** board) {}

// Needed to ensure class is not abstract
void StarBlock::anticlockwise(string** board) {}

// Updates board
void StarBlock::updateBoard(std::string** board) {
	Coordinate *c = blockCoord[0]; // Only looks at first coordinate
	int x = c->getX(c);
	int y = c->getY(c);
	board[x][y] = "*";
}

// Drops star block
void StarBlock::drop(map<int, int> returnRows, string** board, vector<history*> &ongrid, int level, bool &gameOver) {
	returnRows = updateRows(returnRows, board);
	history *h = new history();
	vector<Coordinate*> v = h->accessGrid();

	int maxRow = 3;
	for (int i = 1; i <= bottomRow - maxRow; i++) {
		int delta=i;  //delta is what is added to the x-coord to get the new coord of the block
		int count=0;  
		//determine the new coordinates.
		Coordinate *c = blockCoord[0];
		int x = c->getX(c);
		int newX = x + delta;
		int y = c->getY(c);  //y-coord stays the same.
		//now, we have a new set of coordinates. check if these coordinates are empty. 
		// if yes, drop. if not, do the same process for a diff index(i).
		if (board[newX][y] == " ") {
				++count;
		} 
		if(count != 1) {
			Coordinate *c=blockCoord[0];
			int x=c->getX(c);
			int y=c->getY(c);
			int newX=x+delta-1;
			board[x][y]=" ";  //the previous coordinates of the block are set to empty.
			blockCoord[0]->setCoord(newX, y);
			v.push_back(blockCoord[0]);
			break;
		}

		if (i==bottomRow-maxRow) {
			Coordinate *c=blockCoord[0];
			int x=c->getX(c);
			int y=c->getY(c);
			int newX=x+bottomRow-maxRow;
			board[x][y]=" ";  //the previous coordinates of the block are set to empty.
			blockCoord[0]->setCoord(newX, y);
			v.push_back(blockCoord[0]);
			break;
		}
	}
	h->accessGrid() = v;
	ongrid.push_back(h); // Push history object onto ongrid
}
