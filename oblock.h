#ifndef _OBLOCK_H_
#define _OBLOCK_H_
#include <iostream>
#include "block.h"

class oblock: public block{
public:
	oblock();
	void initialize(std::string** board, int level_num, bool &gameOver) override;
	void clockwise(std::string** board) override;
	void anticlockwise(std::string** board) override;
	void updateBoard(std::string** board) override;
};
#endif
