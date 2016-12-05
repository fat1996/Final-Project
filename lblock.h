#ifndef _LBLOCK_H_
#define _LBLOCK_H_
#include <iostream>
#include "block.h"

class lblock: public block{
public:
	lblock();
	void initialize(std::string** board, int level_num, bool &gameOver) override;
	void clockwise(std::string** board) override;
	void anticlockwise(std::string** board) override;
	void updateBoard(std::string** board) override;
};

#endif
