#ifndef _SBLOCK_H_
#define _SBLOCK_H_
#include <iostream>
#include "block.h"

class sblock: public block{
public:
	sblock();
	void initialize(std::string** board, int level_num) override;
	void clockwise(std::string** board) override;
	void anticlockwise(std::string** board) override;
	void updateBoard(std::string** board) override;
};

#endif
