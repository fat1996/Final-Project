#ifndef _JBLOCK_H_
#define _JBLOCK_H_
#include <iostream>
#include "block.h"

class jblock: public block{
public:
	jblock();
	bool initialize(std::string** board, int level_num) override;
	void clockwise(std::string** board) override;
	void anticlockwise(std::string** board) override;
	void updateBoard(std::string** board) override;
};
#endif
