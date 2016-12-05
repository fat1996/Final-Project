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
#include "window.h"

using namespace std;

// Destructor	
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
	delete w;
}

// Return rows
map<int, int> grid::returnRows(){
	return emptyRows;
}

// Return board
string** grid::returnBoard(){
	return board;
}

// Return grid list
vector<history*> &grid::returnGridList(){
	return GridList;
}

// Returns current score
int &grid::returnCurScore(){
	return currentScore;
}

// Sets up initial configuration of board
void grid::SetBoard(int level_num, string scriptfile, bool& gameOver, bool textOnly) {
	if (!textOnly) {
		w = new Xwindow(400, 600);
	}
	currentScore=0;
	// Initialize board
	board = new string*[boardheight];
	for(int i=0; i<boardheight ; i++) {
		board[i] = new string[boardwidth];
		for(int j = 0; j<boardwidth ; j++) {
			board[i][j]=" ";
		}
	int rowIndex = i;
	emptyRows[rowIndex]=0; //0 means empty. The entire row is empty.	
	}
	// Create level
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

// Draws next block
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

// Draws board in text
void grid::DrawBoard(int l, int hiScore, bool textOnly) {
	cout<<"\nLevel:	  "<<l<<endl;
	cout<<"Score:	  "<<currentScore<<endl;
	cout<<"Hi Score: "<<hiScore<<endl;
	cout<<"---------------"<<endl;
	for (int i=0 ; i<boardheight ;i++) {
		for (int j=0; j<boardwidth; j++){
			cout<<board[i][j];
		}
	cout<<endl;
	}
	cout<<"---------------"<<endl;
	drawNextBlock();

	if (!textOnly) {
		// Graphical display
		w->fillRectangle(0, 0, 400, 600, Xwindow::Black);

		int highScore = hiScore;
		int topleft_x = 30;
		int topleft_y = 120;
		int boardSize = 20;
		int cellWidth = 3;

		string levelText = to_string(level->getLevel());
		string curScoreText = to_string(currentScore);
		string highScoreText = to_string(highScore);

		w->drawBigString(topleft_x, 40, "              QUADRIS", Xwindow::White);
		w->drawString(topleft_x, 60, "Level: "+ levelText, Xwindow::White);
		w->drawString(topleft_x, 80, "Current Score: " + curScoreText, Xwindow::White);
		w->drawString(topleft_x, 100, "High Score: " + highScoreText, Xwindow::White);

		for (int i = 0; i < boardheight; i++) {
			for (int j = 0; j < boardwidth; j++) {
				string cell = board[i][j];
				if (cell == "T") {
					w->fillRectangle(topleft_x + j*(boardSize+ cellWidth) + cellWidth, topleft_y + i*(boardSize + cellWidth) + cellWidth, boardSize, boardSize, Xwindow::Red);
				} else if (cell == "L") {
                			w->fillRectangle(topleft_x + j*(boardSize+ cellWidth) + cellWidth, topleft_y + i*(boardSize + cellWidth) + cellWidth, boardSize, boardSize, Xwindow::Blue);
				} else if (cell == "J") {
						w->fillRectangle(topleft_x + j*(boardSize+ cellWidth) + cellWidth, topleft_y + i*(boardSize + cellWidth) + cellWidth, boardSize, boardSize, Xwindow::Yellow);
				} else if (cell == "S") {
					w->fillRectangle(topleft_x + j*(boardSize+ cellWidth) + cellWidth, topleft_y + i*(boardSize + cellWidth) + cellWidth, boardSize, boardSize, Xwindow::Green);
				} else if (cell == "Z") {
					w->fillRectangle(topleft_x + j*(boardSize+ cellWidth) + cellWidth, topleft_y + i*(boardSize + cellWidth) + cellWidth, boardSize, boardSize, Xwindow::Orange);
				} else if (cell == "I") {
					w->fillRectangle(topleft_x + j*(boardSize+ cellWidth) + cellWidth, topleft_y + i*(boardSize + cellWidth) + cellWidth, boardSize, boardSize, Xwindow::Cyan);
				} else if (cell == "O") {
					w->fillRectangle(topleft_x + j*(boardSize+ cellWidth) + cellWidth, topleft_y + i*(boardSize + cellWidth) + cellWidth, boardSize, boardSize, Xwindow::Magenta);
				} else if (cell == "*") {
					w->fillRectangle(topleft_x + j*(boardSize+ cellWidth) + cellWidth, topleft_y + i*(boardSize +     cellWidth) + cellWidth, boardSize, boardSize, Xwindow::Brown);
				} else {
					// Empty cell
					w->fillRectangle(topleft_x + j*(boardSize+ cellWidth) + cellWidth, topleft_y + i*(boardSize + cellWidth) + cellWidth, boardSize, boardSize, Xwindow::Black);
				}
			}
		}
		w->drawString(30, 570, "Created by Simran Kaur and Fatima Taj in Fall 2016", Xwindow::Magenta);
	}
}

// Returns current block
block* grid::getCurrentBlock() {
	return this->currentBlock;
}

// Gets next block based on level
block* grid::getNextBlock(bool &gameOver) {
	this->currentBlock = this->nextBlock;
	currentBlock->initialize(this->board, level->getLevel(), gameOver);
	this->nextBlock = this->level->getNextBlock();
	return this->nextBlock;
}

// Returns next block
block* grid::returnNextBlock() {
	return this->nextBlock;
}

// Sets current block: used for starblock
void grid::setCurrentBlock(block* b, bool& gameOver) {
	currentBlock = b;
	currentBlock->initialize(this->board, level->getLevel(), gameOver);
}

// Sets next block: used for starblock
void grid::setNextBlock(block* b) {
	nextBlock = b;
}

// Deletes old level object and links new level object
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

// Deletes old level object and links new level object
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
