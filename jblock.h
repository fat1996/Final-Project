#ifndef _JBLOCK_H_
#define _JBLOCK_H_
#include <iostream>
#include "block.h"

class jblock: public block{
public:
	void initialize() override;
	void printBlock() override;
	void fillBlock(std::string** board) override;
	void drop(std::map<std::string, int> returnCells, std::map<std::string, int> returnRows, std::string** board) override;
};
#endif
