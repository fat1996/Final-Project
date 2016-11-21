#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <map>
#include "coordinate.h"

const int height=15;
const int width=11;

class block {
protected:	
	Coordinate *blockCoord[4];  //pointer to the 4 set of coordinates of a block.
public:
	virtual void initialize()=0;
	virtual void printBlock()=0;
	virtual void fillBlock(std::string** board)=0;
	virtual void drop(std::map<std::string, int> returnCells, std::map<std::string, int> returnRows, std::string** board)=0;
};










#endif
