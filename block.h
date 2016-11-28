#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <map>
#include "coordinate.h"

const int bottomRow=17;
const int leftBorder=0;
const int rightBorder=11;
const int rowCap=11;

class block {
protected:	
	Coordinate *blockCoord[4];  //pointer to the 4 set of coordinates of a block.
	int state;  //for cw motion.
	Coordinate *carriedOver;  //for cw motion.

public:
	virtual	~block();
	virtual void initialize(std::string** board)=0;
	virtual void updateBoard(std::string** board)=0;
	virtual void clockwise(std::string** board)=0;
	virtual void anticlockwise(std::string** board)=0;
	void printBlock();
	//virtual void fillBlock(std::string** board)=0;
	void drop(std::map<std::string, int> returnRows, std::string** board);  
	std::map<std::string, int> updateRows(std::map<std::string, int> returnRows, std::string** board);	
	void left(std::string** board);
	void right(std::string **board);
	void down(std::string **board);
	bool isPresent(int x, int y);	
};
#endif
