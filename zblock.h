#ifndef _ZBLOCK_H_
#define _ZBLOCK_H_
#include <iostream>
#include "block.h"

class zblock: public block{
public:
	zblock();
	void initialize(std::string** board, int level_num, bool &gameOver) override;
	void clockwise(std::string** board) override;
	void anticlockwise(std::string** board) override;
	void updateBoard(std::string** board) override;
};

#endif
