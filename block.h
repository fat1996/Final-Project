#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <map>
#include <vector>
#include "coordinate.h"
#include "history.h"

const int bottomRow=17;
const int leftBorder=0;
const int topBorder=0;
const int rightBorder=11;
const int rowCap=11;

class block {
 protected:
	char type;	
	Coordinate *blockCoord[4];  //pointer to the 4 set of coordinates of a block.
	int state;  //for cw motion.
	Coordinate *carriedOver;  //for cw motion.
	//NEWLY ADDED FIELDS.
	int level;
	bool isHeavy;

 public:
 	block(char c);
	char getType();
	virtual	~block();
	virtual void deleteBlock();
	virtual void initialize(std::string** board, int level_num, bool &gameOver)=0;
	virtual void updateBoard(std::string** board)=0;
	virtual void clockwise(std::string** board)=0;
	virtual void anticlockwise(std::string** board)=0;
	void printBlock();
	virtual void drop(std::map<int, int> returnRows, std::string** board, std::vector<history*> &ongrid, int level, bool &gameOver);  	 std::map<int, int> updateRows(std::map<int, int> returnRows, std::string** board);	
	void left(std::string** board);
	void right(std::string **board);
	void down(std::string **board);
	bool isPresent(int x, int y);	
	void Heavy(std::string **board);  //checks the level on which the block was generated, and executes down accordingly.
	bool updateScore(std::string **board, std::map<int, int> returnRows, std::vector<history*> &ongrid, int &counter, 
					int &curScore, int &highScore, int curLevel, int &count);  //checks if any row has been completely filled. If yes, then shift grid downwards. update score accordingly.
};
#endif
