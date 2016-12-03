#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "level.h"
#include "block.h"

const int boardheight=18;
const int boardwidth=11;

class grid {
	block* currentBlock;
	block* nextBlock;
	Level* level;
	// int score;
	// int hiScore;
	std::string **board;
	//std::map<std::string, int> emptyRows;  //keeps track of which rows are completely filled and which are partially filled.
	std::map<int, int> emptyRows;

public:
	void SetBoard(int level_num, std::string scriptfile);   //this sets up the initial configuration of the board.
	void DrawBoard();
	void drawNextBlock();
	std::string** returnBoard();  //returns the private member, board.
	std::map<int, int> returnRows();  //returns the private member, emptyRows.
	~grid(); //destructor.
	block* getCurrentBlock();
	block* getNextBlock();
	void levelUp();
	void levelDown(std::string scriptfile);
};

